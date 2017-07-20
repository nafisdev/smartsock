
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
String p="0";
const int ledPin = 13; 
int ledState = LOW; 
void setup() {
pinMode(ledPin, OUTPUT);
    USE_SERIAL.begin(9600);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("%d...", t);
        USE_SERIAL.flush();
        delay(1000);
    }

   // WiFiMulti.addAP("JioFi2_HomeA", "Home@1996");
   WiFiMulti.addAP("babaji ki booti", "booti112");
}

void loop() {
    if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
       // USE_SERIAL.print("[HTTP] begin...\n");
       // String c=String("http://tatavt2017.000webhostapp.com/get.php");
        String c=String("http://tatavt2017.000webhostapp.com/get.php?uid=121&did=121");
        for(int i=0;i<4;i++){String c1=c+i;
        USE_SERIAL.print(c1);
        http.begin(c1); //HTTP
       // USE_SERIAL.print("[HTTP] GET...\n");
        int httpCode = http.GET();
        if(httpCode > 0) {
           // USE_SERIAL.printf("code: %d\n", httpCode);
            if(httpCode==429){delay(3600);}
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                if(payload.compareTo(p)==0){}
                else{
                p=payload;
               if(payload.compareTo("1")==0){
               USE_SERIAL.print("switch on"); ledState = HIGH;
               }
               else
               {
                USE_SERIAL.print("switch off");USE_SERIAL.print(p);ledState = LOW;
                }
    digitalWrite(ledPin, ledState);                   
                USE_SERIAL.println(payload);
            }}
        } else {
          //  USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }}
  // digitalWrite(ledPin, HIGH);
}

