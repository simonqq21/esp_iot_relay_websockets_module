#include <Arduino.h>
#include "Webserver_module.h"

WebserverModule wsMod;
IPAddress localIP; 
IPAddress gateway;
IPAddress subnet(255,255,255,0);
IPAddress dns(8,8,8,8);

EEPROMConfig eC;
RTCNTP rtcntp(+8);

void setup() {
  Serial.begin(115200);
  WiFi.begin("QUE-STARLINK", "Quefamily01259");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("Connected to %s\n", WiFi.SSID());
  localIP = WiFi.localIP();
  localIP[3] = 70;
  WiFi.config(localIP, gateway, subnet);
  eC.begin();
  rtcntp.begin();
  wsMod.begin(&eC, &rtcntp);
  eC.setSSID("test-SSID");
  eC.setIPAddress(IPAddress(192,168,5,70));
  eC.setPort(6666);
}

void loop() {

}

