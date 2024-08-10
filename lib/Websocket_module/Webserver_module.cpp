#include "Webserver_module.h"

AsyncWebServer WebserverModule::_server = AsyncWebServer(5555);
AsyncWebSocket WebserverModule::_ws = AsyncWebSocket("/ws");
JsonDocument WebserverModule::_jsonDoc;
char WebserverModule::_strData[200];

// AsyncWebServer _server = AsyncWebServer(5555);
// AsyncWebSocket _ws = AsyncWebSocket("/ws");

// WebserverModule::WebserverModule(): _server(5555), _ws("/ws") {

// }

WebserverModule::WebserverModule() {

}

void WebserverModule::begin() {
    Serial.println("initialized ws");
    _ws.onEvent(onEvent);
    _server.addHandler(&_ws);
    _server.begin();
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
    payloadJSON["ssid"] = "ssid01";
    payloadJSON["ip"] = IPAddress(192,168,5,70);
    payloadJSON["port"] = 5555;
    serializeJson(_jsonDoc, _strData);
    Serial.printf("serialized JSON = %s\n", _strData);
    _ws.textAll(_strData);
}

void WebserverModule::sendRelayState() {

}

void WebserverModule::sendDateTime() {

}

void WebserverModule::sendConfig() {

}


// method to handle requests from the client browser 
void WebserverModule::handleRequest(String type, JsonDocument payloadJSON) {
    if (type == CONNECTION_TYPE) {
        sendConnection(payloadJSON);
    }
    else if (type == RELAY_STATE_TYPE) {
        sendRelayState();
    }
    else if (type == DATETIME_TYPE) {
        sendDateTime();
    }
    else if (type == CONFIG_TYPE) {
        sendConfig();
    }
    else {
        
    }
}


// methods to receive and set new state from client browser 
void WebserverModule::receiveConnection() {

}

void WebserverModule::receiveRelayState() {

}

void WebserverModule::receiveDateTime() {

}

void WebserverModule::receiveConfig() {

}

void WebserverModule::receiveData(String type, JsonDocument payloadJSON) {
    if (type == CONNECTION_TYPE) {

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

