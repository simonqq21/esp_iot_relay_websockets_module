#include <Arduino.h>
#include "Webserver_module.h"

WebserverModule wsMod;

IPAddress localIP; 
IPAddress gateway;
IPAddress subnet(255,255,255,0);
IPAddress dns(8,8,8,8);

EEPROMConfig eC;
RTCNTP rtcntp(+8);
TimeSlot * timeslot;

void setup() {
  DateTime now;
  now = DateTime(2024, 8,15,22,0,0);
  Serial.begin(115200);

  WiFi.begin("QUE-STARLINK", "Quefamily01259");
  // WiFi.begin("", "");
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print(".");
  //   delay(500);
  // }
  delay(3000);
  Serial.printf("Connected to %s\n", WiFi.SSID());
  localIP = WiFi.localIP();
  localIP[3] = 70;
  WiFi.config(localIP, gateway, subnet);
  Serial.println(WiFi.localIP());

  eC.begin();
  rtcntp.begin();
  rtcntp.setGMTOffset(8);
  wsMod.begin(&eC, &rtcntp);
  // set datetime and configuration values 
  // connection
  eC.setSSID("test-SSID");
  eC.setIPAddress(IPAddress(192,168,5,70));
  eC.setPort(5555);
  // datetime
  // rtcntp.setISODateTime("2024/01/02T10:00:00Z");
  // relay state 
  eC.setRelayManualSetting(false);
  // timing configuration
  eC.setName("basil-esp32");
  eC.setNTPEnabled(true);
  eC.setLEDSetting(2);
  eC.setGMTOffset(+8);
  eC.setTimerEnabled(false);
  timeslot = eC.getTimeSlot(2);
  timeslot->setEnabled(true);
  timeslot->setOnStartTimeISOString("08:00:00Z", now);
  timeslot->setOnStartTimeISOString("12:00:00Z", now);
}

void loop() {
  wsMod.checkWiFiStatusLoop();
}

