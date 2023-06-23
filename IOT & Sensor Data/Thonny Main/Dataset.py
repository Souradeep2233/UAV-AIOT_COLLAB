
import dht
from machine import Pin, I2C, ADC
from time import sleep, sleep_ms, sleep_us
from bmp180 import BMP180

def bmp_180():
    busI2C = I2C(1, scl = Pin(22), sda=Pin(21), freq=100000)
    bmp = BMP180(busI2C)
    print( "Atm Pressure: "+ str( bmp.get_pressure()),"Pa")
    sleep(1)
        
def gas_sensors():
    MQ7 = ADC(Pin(34))
    MQ135 = ADC(Pin(35))
    MQ7.atten(ADC.ATTN_11DB)      
    MQ135.atten(ADC.ATTN_11DB)
    MQ7_value = MQ7.read()
    print("MQ7: "+str(MQ7_value),"ppm")
    MQ135_value = MQ135.read()
    print("MQ135: "+str(MQ135_value),"ppm")
    sleep(1)
      
def dht_11():
    d=dht.DHT11(Pin(04))
    d.measure()
    t=d.temperature()
    h=d.humidity()
    print('Temperature:',t,'*C')
    print('Humidity:',h,'%')
    
while True:
    bmp_180()
    gas_sensors()
    dht_11()
    sleep(5)