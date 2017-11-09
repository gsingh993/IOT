#include <SPI.h>
#include <ESP8266WiFi.h>

const char* ssid = "networkId";
const char* password = "networkPassword";
const char* server = "api.carriots.com";
const String apiKey = "hashKey";
const String deviceName = "deviceId";

int ledPin = 3;
int pirPin = 12;
int pirState = LOW;
int valInit = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
    Serial.print("Calibration in Progress");//initialization prompt for the user
    for( int i = 0; i < 20; i++){
      Serial.print(".");//for UX
      delay(1000);
    }
    // Connect to the WiFi
    Serial.println("...Attempting to Connect to ");//prevent errors caused by single concat
    Serial.println(ssid); //use 2 serial print to allow for the concatination of strings. 
    WiFi.begin(ssid, password);

    while (Wifi.status() != WL_CONNECTECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("Network Connected -- IP: ");
    Serial.println(WiFi.localIP());
    }
void sendStream(){ // Carriot Setup
    String textMessage = ""; 
    if (pirState == HIGH){
      textMessage = "Motion has been detected";
    }
    else{
      textMessage = "Check the Sensors";
    }
    WifiClient client;
    if (client.connect(server, 80)){
      Serial.println("Connected");
      String json = "{\"protocol\":\"v2\",\"device\":\""+deviceName+"\",\"at\":\"now\",\"data\":{\"light\":\""+textMessage+"\"}}";
    //  HTTP request
      client.println("POST /streams HTTP/1.1");
      client.println("Host: api.carriots.com");
      client.println("Accept: application/json");
      client.println("User-Agent: Arduino-Carriots");
      client.println("Content-Type: application/json");
      client.print("carriots.apikey: ");
      client.println(APIKEY);
      client.print("Content-Length: ");
      int thisLength = json.length();
      client.println(thisLength);
      client.println("Connection: close");
      client.println();
      client.println(json);
    }
    else{
      Serial.println("Connection Failed");
    }

}

void loop() {
  gpio = digitalRead(pirPin);
  Serial.println(gpio);
  if(gpio == HIGH){
    digitalWrite(ledPin,HIGH)
    if(pirState == LOW){
      Serial.println("Motion Detected");
      pirState = HIGH;
      Serial.println("Send Stream");
      sendStream();
      delay(30000);
    }
  }
  else{
    digitalWrite(ledPin, LOW);
    if(pirState == HIGH){
      Serial.println("Motion Detected, Email Sent");
      pirState = LOW;
    }
  }
}
