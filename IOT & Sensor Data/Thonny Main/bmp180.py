from time import sleep, sleep_ms, sleep_us
from ustruct import unpack as unp

LOW_POWER             = 0
STANDARD              = 1
HIGH_RESOLUTION       = 2
ULTRA_HIGH_RESOLUTION = 3
BMP_ADDR              = 119


class BMP180():
    
    def __init__(self, bus):
        
        self.addr    = BMP_ADDR
        self.busI2C  = bus
        self.ovs     = ULTRA_HIGH_RESOLUTION
        
        self.AC1 = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xAA, 2) )[0]
        self.AC2 = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xAC, 2) )[0]
        self.AC3 = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xAE, 2) )[0]
        self.AC4 = unp(">H", self.busI2C.readfrom_mem(self.addr, 0xB0, 2) )[0]
        self.AC5 = unp(">H", self.busI2C.readfrom_mem(self.addr, 0xB2, 2) )[0]
        self.AC6 = unp(">H", self.busI2C.readfrom_mem(self.addr, 0xB4, 2) )[0]
        
        self.B1 = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xB6, 2) )[0]
        self.B2 = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xB8, 2) )[0]
        
        self.MB = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xBA, 2) )[0]
        self.MC = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xBC, 2) )[0]
        self.MD = unp(">h", self.busI2C.readfrom_mem(self.addr, 0xBE, 2) )[0]
        
        #print("Calibration DATA")
        #print( "AC1: "+ str( self.AC1 ) )
       # print( "AC2: "+ str( self.AC2 ) )
       # print( "AC3: "+ str( self.AC3 ) )
       # print( "AC4: "+ str( self.AC4 ) )
        #print( "AC5: "+ str( self.AC5 ) )
        #print( "AC6: "+ str( self.AC6 ) )
        #print( "B1: "+ str( self.B1 ) )
        #print( "B2: "+ str( self.B2 ) )
        #print( "MB: "+ str( self.MB ) )
        #print( "MC: "+ str( self.MC ) )
        #print( "MD: "+ str( self.MD ) )
        
        self.UT_raw   = None
        self.UP_raw   = None
        
        self.MSB_raw  = None
        self.LSB_raw  = None
        self.XLSB_raw = None
        self.B5       = None
        
    def makegauge(self):
        delayconst = (5,8,14,26)
        
        #temp raw
        self.busI2C.writeto_mem(self.addr, 0xF4,  bytearray( [0x2E] ) )
        sleep_ms(5)
        self.UT_raw = self.busI2C.readfrom_mem(self.addr, 0xF6, 2)
        
        #pressure raw
        self.busI2C.writeto_mem(self.addr, 0xF4,  bytearray( [0x34+(self.ovs<<6)] ) )
        sleep_ms( delayconst[self.ovs] )
        
        self.MSB_raw  = self.busI2C.readfrom_mem(self.addr, 0xF6, 1)
        self.LSB_raw  = self.busI2C.readfrom_mem(self.addr, 0xF7, 1)
        self.XLSB_raw = self.busI2C.readfrom_mem(self.addr, 0xF8, 1)
        
        
    
    def get_temperature(self):
        self.makegauge()
        UT = unp('>h', self.UT_raw)[0]
        X1 = (UT-self.AC6)*self.AC5/2**15
        X2 = self.MC*2**11/(X1+self.MD)
        self.B5 = X1+X2
        return (((X1+X2)+8)/2**4)/10
    
    def get_pressure(self):
        
        self.get_temperature()
        
        MSB = unp('B', self.MSB_raw)[0]
        LSB = unp('B', self.LSB_raw)[0]
        XLSB = unp('B', self.XLSB_raw)[0]
        
        UP = ((MSB << 16)+(LSB << 8)+XLSB) >> (8-self.ovs)
        B6 = self.B5-4000
        X1 = (self.B2*(B6**2/2**12))/2**11
        X2 = self.AC2*B6/2**11
        X3 = X1+X2
        B3 = ((int((self.AC1*4+X3)) << self.ovs)+2)/4
        X1 = self.AC3*B6/2**13
        X2 = (self.B1*(B6**2/2**12))/2**16
        X3 = ((X1+X2)+2)/2**2
        B4 = abs(self.AC4)*(X3+32768)/2**15
        B7 = (abs(UP)-B3) * (50000 >> self.ovs)
        if B7 < 0x80000000:
            pressure = (B7*2)/B4
        else:
            pressure = (B7/B4)*2
        X1 = (pressure/2**8)**2
        X1 = (X1*3038)/2**16
        X2 = (-7357*pressure)/2**16
        return (pressure+(X1+X2+3791)/2**4)
    