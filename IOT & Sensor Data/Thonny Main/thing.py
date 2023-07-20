import machine
import urequests 
import network, time
import dht
from machine import Pin, I2C, ADC
from time import sleep, sleep_ms, sleep_us
from bmp180 import BMP180

HTTP_HEADERS = {'Content-Type': 'application/json'} 
THINGSPEAK_WRITE_API_KEY = 'MW6OE1EQM9OX949U' 

UPDATE_TIME_INTERVAL = 5000  # in ms 
last_update = time.ticks_ms() 

ssid='IEM IEDC LAB'
password='IEMIEDC501'

# Configure ESP32 as Station
sta_if=network.WLAN(network.STA_IF)
sta_if.active(True)

if not sta_if.isconnected():
    print('connecting to network...')
    sta_if.connect(ssid, password)
    while not sta_if.isconnected():
     pass
print('network config:', sta_if.ifconfig()) 

def sensor_data():
	#BMP180
    busI2C = I2C(1, scl = Pin(22), sda=Pin(21), freq=100000)
    bmp = BMP180(busI2C)
    p=bmp.get_pressure()
    
    #MQ sensors
    MQ7 = ADC(Pin(34))
    MQ135 = ADC(Pin(35))
    MQ7.atten(ADC.ATTN_11DB)      
    MQ135.atten(ADC.ATTN_11DB)
    MQ7_value = MQ7.read()
    MQ135_value = MQ135.read()

	#DHT11
    d=dht.DHT11(Pin(04))
    d.measure()
    t=d.temperature()
    h=d.humidity()

	#sending data to cloud
    sensor_readings = {'field1':MQ7_value, 'field2':MQ135_value,'field3':t, 'field4':h,'field5':p}
    request = urequests.post( 'https://api.thingspeak.com/update?api_key=MW6OE1EQM9OX949U', json = sensor_readings, headers = HTTP_HEADERS )  
    request.close() 
    print(sensor_readings)

while True: 
    if time.ticks_ms() - last_update >= UPDATE_TIME_INTERVAL:
		sensor_data()
		sleep(5)