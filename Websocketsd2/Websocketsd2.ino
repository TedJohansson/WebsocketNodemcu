#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>
WebSocketsServer webSocket = WebSocketsServer(81);
const char* ssid     = "WIFI NAME";
const char* password = "WIFI PASSWORD";
const int bluePin = 13;
const int redPin = 15;
const int greenPin = 12;
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            break;
            
        case WStype_CONNECTED:
         {
                IPAddress ip = webSocket.remoteIP(num);
         }
            break;
        case WStype_TEXT:
        {
            
          String text = String((char *) &payload[0]);
          
          if(text=="Computer on"){
           
            digitalWrite(5, LOW);
            Serial.println("led just lit");
            webSocket.sendTXT(num, "led just lit", lenght);
            }
            
           if(text=="Computer off"){
           
            digitalWrite(5, HIGH);
            Serial.println("reset");
            
            }
                            
        }
            
           
        webSocket.sendTXT(num, payload, lenght);
        webSocket.broadcastTXT(payload, lenght);
        break;
        
        case WStype_BIN:
     
            hexdump(payload, lenght);

            // echo data back to browser
            webSocket.sendBIN(num, payload, lenght);
            break;
    }

}


void setup() {
   
    Serial.begin(115200);
    pinMode(5,OUTPUT);
    digitalWrite(5, HIGH);
   WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
  Serial.println(WiFi.localIP());
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
}
