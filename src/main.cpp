#include <Arduino.h>
#include "Webserver_module.h"

WebserverModule wsMod;
EEPROMConfig eC(0);
RTCNTP rtcntp(+8);
TimeSlot * timeslot;

void dummySendConnectionFunc() {
  Serial.println("run send connection function");
}

void dummySendRelayStateFunc() {
  Serial.println("run send relay state function");
}

void dummySendDatetimeFunc() {
  Serial.println("run send datetime function");
}

void dummySendConfigFunc() {
  Serial.println("run send config function");
}

void dummyReceiveConnectionFunc() {
  Serial.println("run receive connection function");
}

void dummyReceiveRelayStateFunc() {
  Serial.println("run receive relay state function");
}

void dummyReceiveDatetimeFunc() {
  Serial.println("run receive datetime function");
}

void dummyReceiveConfigFunc() {
  Serial.println("run receive config function");
}

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  DateTime now;
  Serial.begin(115200);

  eC.begin();
  eC.load();

  wsMod.scanWiFi();
  wsMod.begin(&eC, &rtcntp);
  wsMod.connect();
  
  wsMod.setSendConnectionCallback();
  wsMod.setSendDateTimeCallback(dummySendDatetimeFunc);
  wsMod.setSendRelayStateCallback(dummySendRelayStateFunc);
  wsMod.setSendConfigCallback(dummySendConfigFunc);
  wsMod.setReceiveConnectionCallback(dummyReceiveConnectionFunc);
  wsMod.setReceiveDateTimeCallback(dummyReceiveDatetimeFunc);
  wsMod.setReceiveRelayStateCallback(dummyReceiveRelayStateFunc);
  wsMod.setReceiveConfigCallback();

  rtcntp.begin();
  rtcntp.setGMTOffset(8);
  rtcntp.refreshNTPTime();
  rtcntp.updateRTCWithNTP();
  now = rtcntp.getRTCTime();
  Serial.println(rtcntp.getISODateTime());

  eC.load(now);



  // // set datetime and configuration values 
  // // connection
  // eC.setSSID("test-SSID");
  // eC.setIPAddress(IPAddress(192,168,5,70));
  // eC.setPort(5555);
  // // datetime
  // // rtcntp.setISODateTime("2024/01/02T10:00:00Z");
  // // relay state 
  // eC.setRelayManualSetting(false);
  // // timing configuration
  // eC.setName("basil-esp32");
  // eC.setNTPEnabled(true);
  // eC.setLEDSetting(2);
  // eC.setGMTOffset(+8);
  // eC.setTimerEnabled(false);
  // timeslot = eC.getTimeSlot(2);
  // timeslot->setEnabled(true);
  // timeslot->setOnStartTimeISOString("08:00:00Z", now);
  // timeslot->setOnStartTimeISOString("12:00:00Z", now);

  // WiFi.disconnect();
}

void loop() {
  // Serial.println(0);
  wsMod.checkWiFiStatusLoop();
  // wsMod.sendWiFiScanResults();
}

