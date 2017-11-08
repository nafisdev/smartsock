#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;
const String id1=""; //Enter The Switch ID here
const String id2=""; //Enter The Switch ID here
const String id3="";//Enter The Switch ID here
const String id4=""; //Enter The Switch ID here
void setup() {
  USE_SERIAL.begin(9600);
 for (uint8_t t = 4; t > 0; t--) {
 USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  WiFiMulti.addAP("NQ", "farewell"); //Enter the Wi-Fi Detai;s here
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
}
void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
   // configure traged server and url
      http.begin("https://192.168.1.12/test.html" ); 
//HTTPS  
//http.begin("https://tatavt2017.000webhostapp.com/get2.php?s1=403&s2=405&s3=407&s4=909"); //HTTP
//http.begin("https://en.wikipedia.org/wiki/Language");
    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
        String s1, s2, s3, s4;
        s1 = payload.charAt(0);
        s2 = payload.charAt(1);
        s3 = payload.charAt(2);
        s4 = payload.charAt(3);
        if (s1.equalsIgnoreCase("1"))
        {
          USE_SERIAL.println("ON");
          digitalWrite(D7, LOW);
        }
        else
        {
          USE_SERIAL.println("OFF");
          digitalWrite(D7, HIGH);
        }
        if (s2.equalsIgnoreCase("1"))
        {
          USE_SERIAL.println("ON");
          digitalWrite(D6, LOW);
        }
        else
        {
          USE_SERIAL.println("OFF");
          digitalWrite(D6, HIGH);
        }
        if (s3.equalsIgnoreCase("1"))
        {
          USE_SERIAL.println("ON");
          digitalWrite(D1, LOW);
        }
        else
        {
          USE_SERIAL.println("OFF");
          digitalWrite(D1, HIGH);
        }
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  delay(0);
}

