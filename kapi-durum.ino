#include <WiFi.h>

// LED ve reedswitch icin GPIO ayari.
const int reedSwitch = 4;
const int led = 2; 

// Kapinin durumunu aldigimiz boolean
bool changeState = false;

// reedswitch durumu (1=acik, 0=kapali)
bool state;
String doorState;

// yalnizca 1500 milisaniye araliktaki degisiklikleri algilayabilcegimiz degiskenler
unsigned long previousMillis = 0; 
const long interval = 1500;

// ssid password ve apikey bilgilerimi guvenlik amaci ile buradan kaldirdim. 
const char* ssid = "";
const char* password = "";
const char* host = "maker.ifttt.com";
const char* apiKey = "";

// reedswitch durumu degistirdiginde calisir
ICACHE_RAM_ATTR void changeDoorStatus() {
  Serial.println("State changed");
  changeState = true;
}

void setup() {
  // Serial portumuz
  Serial.begin(115200);

  // suanki kapi durumunu okumak
  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  // led durumu ile kapi durumu eslesmesi
  pinMode(led, OUTPUT);
  digitalWrite(led, !state);
  
  // reedswitch pinini interruprt olarak ayarlayip change mod ayarlama
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  // Wi-Fi baglanmak
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
}

void loop() {
  if (changeState){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      // mevcut kapi durumunu ters cevirme   
      state = !state;
      if(state) {
        doorState = "closed";
      }
      else{
        doorState = "open";
      }
      digitalWrite(led, !state);
      changeState = false;
      Serial.println(state);
      Serial.println(doorState);

      // email gondermek
      Serial.print("connecting to ");
      Serial.println(host);
      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
      }

      String url = "/trigger/door_status/with/key/";
      url += apiKey;

      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" + 
                     "Content-Type: application/x-www-form-urlencoded\r\n" + 
                     "Content-Length: 13\r\n\r\n" +
                     "value1=" + doorState + "\r\n");
    }  
  }
}
