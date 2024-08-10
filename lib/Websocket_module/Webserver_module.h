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

from ESP32 to browser
- ESP32 send connection details to browser
{
    type: "connection",
    ssid: string,
    ip: string,
    port: int,
}

- ESP32 send relay state to browser
{
    type: "relay_state",
    relay_state: bool,
}

- ESP32 send system date and time to browser
{
    type: "datetime", 
    datetime: string (ISO datetime format),
}

- ESP32 send main configuration to browser
{
    type: "config",
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
}



from browser to ESP32
- Browser request connection details from ESP32
{
    type: "request",
    request_type: "connection",
}

- Browser send connection details to ESP32
{
    type: "connection",
    ssid: string,
    pass: string,
    ip: string,
    port: int,
}

- Browser request relay state from ESP32
{
    type: "request",
    request_type: "relay_state",
}

- Browser send and set relay state to ESP32
{
    type: "relay_state", 
    relay_state: bool,
}

- Browser request system date and time from ESP32
{
    type: "request",
    request_type: "datetime",
}

- Browser send and set system date and time to ESP32
{
    type: "datetime", 
    datetime: string (ISO datetime format),
}

- Browser request main configuration from ESP32
{
    type: "request",
    request_type: "config",
}

- Browser send and set main configuration to ESP32
{
    type: "config",
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
        static void sendConnectionDetails();
        static void sendRelayState();
        static void sendSystemDateTime();
        static void sendMainConfig();

        // method to handle requests from the client browser 
        static void handleRequest();

        // methods to receive and set new state from client browser 
        static void receiveConnectionDetails();
        static void receiveRelayState();
        static void receiveSystemDateTime();
        static void receiveMainConfig();
    private:
        static AsyncWebServer _server;
        static AsyncWebSocket _ws;
        static JsonDocument _jsonDoc;
        static char strData[200];
};

#endif