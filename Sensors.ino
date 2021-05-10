#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//#include <SimpleTimer.h>
#include "DHT.h"
BlynkTimer timer;
//SimpleTimer timer;
char auth[] = "bqxkbv03yM5TEXZByT0jlE5HjPYktMDF";

char ssid[] = "Redmi 6";
char pass[] = "khaleesi";
int in1 = 12;
int sensor = 27;
int led = 26;
unsigned long t=0;

#define MQ2 34
#define PIR 22
#define GREEN 16
#define RED 17
#define DHTPIN 4  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int sensorValue_mq2 = 0;
boolean state = false;

void setup()
{
 // Debug console
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
 pinMode(MQ2, INPUT);
 pinMode(PIR, INPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(RED, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(sensor, INPUT);
 pinMode(led, OUTPUT);
  
 digitalWrite(in1,HIGH);
 digitalWrite(led,LOW);

 while(millis()<13000)
  {
    digitalWrite(led,HIGH);
    delay(50);
    digitalWrite(led,LOW);
    delay(50);
  }
  digitalWrite(led,LOW);
// Serial.begin(9600);
 Serial.println(F("DHTxx test!"));
 dht.begin();
 timer.setInterval(1000L, sendUptime);
}
void sendUptime()
{
  sensorValue_mq2 = analogRead(MQ2);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  bool isDetected = digitalRead(PIR);
  Blynk.virtualWrite(V1, sensorValue_mq2);
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
  Blynk.virtualWrite(V2, isDetected);
  Serial.print("Gas Value: ");
  Serial.println(sensorValue_mq2);
  Serial.print("PIR value:");
  Serial.println(isDetected);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  
  
  if (sensorValue_mq2 > 1000)
  {
  Blynk.notify("Gas Detected!");
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
  }
  else if (t >=  25 )
  {
  Blynk.email("agrawalchanchal453@gmail.com","ESP32 Alert","Temperature above 30!");
  Blynk.notify("Temperature too high!");
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
  }
  else
  {
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  }
  if (isnan(h) || isnan(t)) {
   Serial.println("Failed to read from DHT sensor!");
   return;
  }
  if(isDetected){
    Serial.println("Presence detected");
  }
  else{
    Serial.println("Presence not Detected");
  }
  
}
 
void loop()
{
 Blynk.run();
 timer.run();
 digitalWrite(in1,HIGH);
  digitalWrite(led,LOW);
  if(digitalRead(sensor)==HIGH)
  {
   t=millis();
   while(millis()<(t+5000))
   {
   digitalWrite(in1,LOW);
   digitalWrite(led,HIGH);
     if((millis()>(t+2300))&&(digitalRead(sensor)==HIGH))
      {
       t=millis();
      }
   }
  }
}
