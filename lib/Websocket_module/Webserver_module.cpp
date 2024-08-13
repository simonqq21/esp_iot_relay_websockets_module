#include "Webserver_module.h"

AsyncWebServer WebserverModule::_server = AsyncWebServer(5555);
AsyncWebSocket WebserverModule::_ws = AsyncWebSocket("/ws");
JsonDocument WebserverModule::_jsonDoc;
char WebserverModule::_strData[1250];
EEPROMConfig* WebserverModule::_eC;
RTCNTP* WebserverModule::_rtcntp;

// AsyncWebServer _server = AsyncWebServer(5555);
// AsyncWebSocket _ws = AsyncWebSocket("/ws");
// WebserverModule::WebserverModule(): _server(5555), _ws("/ws") {
// }

WebserverModule::WebserverModule() {

}

void WebserverModule::begin(EEPROMConfig* eC, RTCNTP* rtcntp) {
    _eC = eC;
    _rtcntp = rtcntp;
    _ws.onEvent(onEvent);
    _server.addHandler(&_ws);
    _server.begin();
    Serial.println("initialized ws");
}

void WebserverModule::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;

        DeserializationError error = deserializeJson(_jsonDoc, (char*)data); 
        String cmd = _jsonDoc[CMD_KEY];
        String type = _jsonDoc[TYPE_KEY];
        // String payload = _jsonDoc[PAYLOAD_KEY]["ssid"];
        JsonDocument payloadJSON = _jsonDoc[PAYLOAD_KEY];

        Serial.printf("cmd=%s\n", cmd);
        Serial.printf("type=%s\n", type);
        // Serial.printf("payload=%s\n", payloadJSON["ssid"]);
        // String ssid = payloadJSON["ssid"];
        // Serial.printf("ssid=%s\n", ssid);
        // Serial.printf("payload2=%s\n", payload2);
        // char output[100];
        // serializeJson(_jsonDoc, output);
        // Serial.print(output);
        // JsonDocument pj;
        // deserializeJson(pj, _jsonDoc[PAYLOAD_KEY]);
        // JsonObject payload = pj.as<JsonObject>();
        // Serial.printf("%s\n", pj["ssid"]);
        
        if (cmd == REQUEST_CMD) {
            handleRequest(type, payloadJSON);
        }
        else if (cmd == SAVE_CMD) {
            receiveData(type, payloadJSON);
        }
    }
}

void WebserverModule::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
    void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

// methods to send ESP32 state to client browser
void WebserverModule::sendConnection(JsonDocument inputPayloadJSON) {
    _jsonDoc.clear();
    _jsonDoc[CMD_KEY] = LOAD_CMD;
    _jsonDoc[TYPE_KEY] = CONNECTION_TYPE;
    JsonObject payloadJSON = _jsonDoc[PAYLOAD_KEY].to<JsonObject>();
    payloadJSON["ssid"] = _eC->getSSID();
    payloadJSON["ip"] = _eC->getIPAddress();
    payloadJSON["port"] = _eC->getPort();
    serializeJson(_jsonDoc, _strData);
    Serial.printf("serialized JSON = %s\n", _strData);
    _ws.textAll(_strData);
}

void WebserverModule::sendRelayState(JsonDocument inputPayloadJSON) {
    _jsonDoc.clear();
    _jsonDoc[CMD_KEY] = LOAD_CMD;
    _jsonDoc[TYPE_KEY] = RELAY_STATE_TYPE;
    JsonObject payloadJSON = _jsonDoc[PAYLOAD_KEY].to<JsonObject>();
    payloadJSON["relay_state"] = _eC->getRelayManualSetting();
    serializeJson(_jsonDoc, _strData);
    Serial.printf("serialized JSON = %s\n", _strData);
    _ws.textAll(_strData);
}

void WebserverModule::sendDateTime(JsonDocument inputPayloadJSON) {
    _jsonDoc.clear();
    _jsonDoc[CMD_KEY] = LOAD_CMD;
    _jsonDoc[TYPE_KEY] = DATETIME_TYPE;
    JsonObject payloadJSON = _jsonDoc[PAYLOAD_KEY].to<JsonObject>();
    payloadJSON["datetime"] = _rtcntp->getISODateTime();
    serializeJson(_jsonDoc, _strData);
    Serial.printf("serialized JSON = %s\n", _strData);
    _ws.textAll(_strData);
}

void WebserverModule::sendConfig(JsonDocument inputPayloadJSON) {
    _jsonDoc.clear();
    _jsonDoc[CMD_KEY] = LOAD_CMD;
    _jsonDoc[TYPE_KEY] = CONFIG_TYPE;
    JsonObject payloadJSON = _jsonDoc[PAYLOAD_KEY].to<JsonObject>();
        payloadJSON["name"] = _eC->getName();
        payloadJSON["ntpEnabledSetting"] = _eC->getNTPEnabled();
        payloadJSON["gmtOffsetSetting"] = _eC->getGMTOffset();
        payloadJSON["timerEnabledSetting"] = _eC->getTimerEnabled();
        payloadJSON["ledSetting"] = _eC->getLEDSetting();
        payloadJSON["relayManualSetting"] = _eC->getRelayManualSetting();
        JsonArray timeSlotsJSON = payloadJSON["timeSlots"].to<JsonArray>();
        JsonObject timeSlotJSON;
        for (int i=0;i<NUMBER_OF_TIMESLOTS;i++) {
            TimeSlot* curTS = _eC->getTimeSlot(i);
            timeSlotJSON = timeSlotsJSON.add<JsonObject>();
            timeSlotJSON["index"] = curTS->getIndex();
            timeSlotJSON["enabled"] = curTS->getEnabled();
            timeSlotJSON["onStartTime"] = curTS->getOnStartTimeISOString();
            timeSlotJSON["onEndTime"] = curTS->getOnEndTimeISOString();
            timeSlotJSON["durationInSeconds"] = curTS->getDuration();
        }

    serializeJson(_jsonDoc, _strData);
    Serial.printf("serialized JSON = %s\n", _strData);
    _ws.textAll(_strData);
}


// method to handle requests from the client browser 
void WebserverModule::handleRequest(String type, JsonDocument payloadJSON) {
    if (type == CONNECTION_TYPE) {
        sendConnection(payloadJSON);
    }
    else if (type == RELAY_STATE_TYPE) {
        sendRelayState(payloadJSON);
    }
    else if (type == DATETIME_TYPE) {
        sendDateTime(payloadJSON);
    }
    else if (type == CONFIG_TYPE) {
        sendConfig(payloadJSON);
    }
    else {
        
    }
}

// methods to receive and set new state from client browser 
void WebserverModule::receiveConnection(JsonDocument inputPayloadJSON) {

}

void WebserverModule::receiveRelayState(JsonDocument inputPayloadJSON) {

}

void WebserverModule::receiveDateTime(JsonDocument inputPayloadJSON) {

}

void WebserverModule::receiveConfig(JsonDocument inputPayloadJSON) {

}

void WebserverModule::receiveData(String type, JsonDocument payloadJSON) {
    if (type == CONNECTION_TYPE) {
        receiveConnection(payloadJSON);
    }
    else if (type == RELAY_STATE_TYPE) {

    }
    else if (type == DATETIME_TYPE) {

    }
    else if (type == CONFIG_TYPE) {

    }
    else {

    }
}

