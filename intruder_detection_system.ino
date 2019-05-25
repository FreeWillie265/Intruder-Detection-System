
//#define BLYNK_MAX_SENDBYTES 128

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "your blynk auth token";
int pirPin = D7;

long before = 0;

// Your WiFi credentials.
char ssid[] = "ssid";
char pass[] = "password";


void sendEmail(){
  Serial.println("Sending Email!"); // This can be seen in the Serial Monitor
  Blynk.email("your email address", "Intruder Detected", "An Intruder has been detected in your property!");
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(pirPin, INPUT);   // declare sensor as input
  Blynk.begin(auth, ssid, pass);
  before = millis();
  Serial.print("Initialized!");
}

void loop()
{
  getPirValue();
  Blynk.run();
}

void getPirValue(){
  if(digitalRead(pirPin)){
    Serial.println("Intruder Detected!"); 
      /*
     *send an email 
     *Make sure no two emails are sent in the same minute
     */
    if(millis() - before > 1000 * 15){ //change back to 60s
      sendEmail();
      before = millis();  
    }
  }
  delay(500);
}
