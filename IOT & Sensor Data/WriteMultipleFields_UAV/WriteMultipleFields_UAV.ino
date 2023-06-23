#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Wire.h>
#include "BMP085.h"
//#include <Adafruit_BMP085.h>
//Adafruit_BMP085 bmp;
#include <DHT.h>
#define DHTPIN 04
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

float pressure;
float mbar;
BMP085 myBarometer; // initialise pressure sensor

int MQ135_analog = 35;
int MQ7_analog = 34;

void setup() {
  Serial.begin(115200);  //Initialize serial
  dht.begin(); 
  myBarometer.init();
  pinMode(MQ7_analog, INPUT); 
  pinMode(MQ135_analog, INPUT);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print(h);
  Serial.println(" %");
  Serial.print(t);
    Serial.println(" °C");

pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); // read pressure value in pascals
  mbar = pressure / 100; // convert millibar to pascals
  
//  Serial.print("Pressure at sealevel (calculated) = ");
 // int p=bmp.readSealevelPressure();
  Serial.print(mbar);
  Serial.println(" Pa");
  int MQ135_read = analogRead(MQ135_analog);
  int MQ7_read = analogRead(MQ7_analog);
  Serial.print(MQ135_read);
      Serial.println(" ppm");
  Serial.print(MQ7_read);
      Serial.println(" ppm");
 
  // set the fields with the values
  ThingSpeak.setField(1, MQ7_read);
  ThingSpeak.setField(2, MQ135_read);
  ThingSpeak.setField(3, t);
  ThingSpeak.setField(4, h);
  ThingSpeak.setField(5, mbar);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000); // Wait 20 seconds to update the channel again
}
