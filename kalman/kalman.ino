#include "ArduiKalman.h"
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

#define MQ135_analog 35
#define MQ7_analog 34
#define UPDATE_TIME  100
long current; 

int stateNum = 1;
int measureNum = 1;

//init matrix for Kalman
float xc[1];
float xc1[1];// correct state vector 
float xp[1];        // predict state vector 
float A[1][1];      // prediction error covariance 
float Q[1][1];      // process noise covariance 
float R[1][1];      // measurement error covariance
float H[1][1];      // Measurement model
float P[1][1];      // Post-prediction, pre-update
  
KalmanFilter m_kf;
KalmanFilter m_kf1;

void setup() {
// put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(3.3);  // To freeze the upper limit
  Serial.print(" ");
  
  dht.begin(); 
  myBarometer.init();
  pinMode(MQ7_analog, INPUT); 
  pinMode(MQ135_analog, INPUT);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);
  
  m_kf.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc[0]);
  m_kf.zeros();
  m_kf1.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc1[0]);
  m_kf1.zeros();
  A[0][0] = 1.0f;
  H[0][0] = 1.0f;
  Q[0][0] = 0.01f;
  R[0][0] = 100.0f;
  P[0][0] = 1.0f;
  xc[0] = analogRead(MQ7_analog);
  xc1[0] = analogRead(MQ135_analog);
}

void loop() {  
  // predict
  float *predict = m_kf.predict();
  // correct
  float measured_value = analogRead(MQ7_analog);
  float measurement[measureNum];
  measurement[0] = measured_value;
  float *correct = m_kf.correct(measurement);
  float estimated_value_MQ7 = correct[0];
  //Serial.println();

  float *predict1 = m_kf1.predict();
  // correct
  float measured_value1 = analogRead(MQ135_analog);
  float measurement1[measureNum];
  measurement1[0] = measured_value1;
  float *correct1 = m_kf1.correct(measurement1);
  float estimated_value_MQ135 = correct1[0];
  
  //Serial.println();
 // delay(1000);
  
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
  Serial.print(mbar);
  Serial.println(" Pa");

  Serial.print("MQ7 ");
  Serial.println(estimated_value_MQ7);
  Serial.print("MQ135 ");
  Serial.println(estimated_value_MQ135);
  
  // set the fields with the values
  ThingSpeak.setField(1,estimated_value_MQ7);
  ThingSpeak.setField(2,estimated_value_MQ135);
  ThingSpeak.setField(3,t);
  ThingSpeak.setField(4,h);
  ThingSpeak.setField(5,mbar);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
    Serial.println(" ");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000); // Wait 20 seconds to update the channel again

}
