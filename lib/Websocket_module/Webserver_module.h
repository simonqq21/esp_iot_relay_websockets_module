#ifndef WEBSERVER_MODULE_H
#define WEBSERVER_MODULE_H
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "ArduinoJson.h"

#include "EEPROMConfig.h"

/*
Other libraries and modules to include:
IO module
RTC module
EEPROM configuration module 


messages:
Standard contents of every JSON payload:
{
    cmd: string,
    type: string,
    payload: any,
}



from ESP32 to browser
- ESP32 send connection details to browser
{
    cmd: "load",
    type: "connection",
    payload: {
        ssid: string,
        ip: string,
        port: int,
    },
}

- ESP32 send relay state to browser
{
    cmd: "load",
    type: "relay_state",
    payload: {
        relay_state: bool,
    },
}

- ESP32 send system date and time to browser
{
    cmd: "load",
    type: "datetime", 
    payload: {
        datetime: string (ISO datetime format),
    },
}

- ESP32 send main configuration to browser
{
    cmd: "load",
    type: "config",
    payload: {
        name: string,
        ntpEnabledSetting: bool,
        gmtOffsetSetting: int, 
        timerEnabledSetting: bool,
        ledSetting: int,
        relayManualSetting: bool,
        timeSlots[]: timeSlot[] {
            index: int,
            initialized: int,
            enabled: bool,
            onStartTime: string (ISO datetime),
            onEndTime: string (ISO datetime),
            durationInSeconds: int,
        },
    },
}



from browser to ESP32
- Browser request connection details from ESP32
{
    cmd: "request",
    type: "connection",
    payload: {
    },
}

- Browser request relay state from ESP32
{
    cmd: "request",
    type: "relay_state",
    payload: {
    },
}

- Browser request system date and time from ESP32
{
    cmd: "request",
    type: "datetime",
    payload: {
    },
}

- Browser request main configuration from ESP32
{
    cmd: "request",
    type: "config",
    payload: {
    },
}

- Browser send connection details to ESP32
{
    cmd: "save",
    type: "connection",
    payload: {
        ssid: string,
        pass: string,
        ip: string,
        port: int,
    },
}

- Browser send and set relay state to ESP32
{
    cmd: "save",
    type: "relay_state", 
    payload: {
        relay_state: bool,
    },
}

- Browser send and set system date and time to ESP32
{
    cmd: "save",
    type: "datetime", 
    payload: {
        datetime: string (ISO datetime format),
    },
}

- Browser send and set main configuration to ESP32
{
    cmd: "save",
    type: "config",
    payload: {
        name: string,
        ntpEnabledSetting: bool,
        gmtOffsetSetting: int, 
        timerEnabledSetting: bool,
        ledSetting: int,
        relayManualSetting: bool,
        timeSlots[]: timeSlot[] {
            index: int,
            initialized: int,
            enabled: bool,
            onStartTime: string (ISO datetime),
            onEndTime: string (ISO datetime),
            durationInSeconds: int,
        },
    },
}
*/

class WebserverModule {
    public:
        WebserverModule();
        static void begin();
        static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
            void *arg, uint8_t *data, size_t len);
        static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

        // methods to send ESP32 state to client browser
        static void sendConnection();
        static void sendRelayState();
        static void sendDateTime();
        static void sendConfig();
        // method to handle requests from the client browser 
        static void handleRequest(String type, JsonDocument payloadJSON); 

        // methods to receive and set new state from client browser 
        static void receiveConnection();
        static void receiveRelayState();
        static void receiveDateTime();
        static void receiveConfig();
        // method to handle receiving different kinds of data from the client browser 
        static void receiveData(String type, JsonDocument payloadJSON);

    private:
        static AsyncWebServer _server;
        static AsyncWebSocket _ws;
        static JsonDocument _jsonDoc;
        static char strData[200];
};

#endif