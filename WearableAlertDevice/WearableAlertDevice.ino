#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerWifi.h>

ThingerWiFi thing("AlertWearable" , "NM1" , "123456");
int pushPin = 12; 
int ledPin = 3;
int init = 0;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(pushPin, INPUT_PULLUP);
    Serial.begin(9600);
    thing.add_wifi("networdId", "networkPassword");
    Serial.println("Setting up the network");
}

void loop() {
  init = digitalRead(pushPin);
  Serial.println(init);
  if(init == LOW){
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    thing.handle();
    thing.call_endpoint("email");
    delay(5000);
  }
  else{
    digitalWrite(ledPin, LOW); 
  }
}
