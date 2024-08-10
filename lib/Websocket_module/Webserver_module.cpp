#include "Webserver_module.h"

AsyncWebServer WebserverModule::_server = AsyncWebServer(5555);
AsyncWebSocket WebserverModule::_ws = AsyncWebSocket("/ws");
JsonDocument WebserverModule::_jsonDoc;
char WebserverModule::strData[200];

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
        String cmd = _jsonDoc["cmd"];
        String type = _jsonDoc["type"];
        // String payload = _jsonDoc["payload"]["ssid"];
        JsonDocument payloadJSON = _jsonDoc["payload"];

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
        // deserializeJson(pj, _jsonDoc["payload"]);
        // JsonObject payload = pj.as<JsonObject>();
        // Serial.printf("%s\n", pj["ssid"]);
        
        if (cmd == "request") {
            handleRequest(type, payloadJSON);
        }
        else if (cmd == "save") {
            // if (type == "connection") {

            // }
            // else if (type == "relay_state") {

            // }
            // else if (type == "datetime") {

            // }
            // else if (type == "config") {

            // }
            // else {

            // }
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
void WebserverModule::sendConnection() {

}

void WebserverModule::sendRelayState() {

}

void WebserverModule::sendDateTime() {

}

void WebserverModule::sendConfig() {

}


// method to handle requests from the client browser 
void WebserverModule::handleRequest(String type, JsonDocument payloadJSON) {
    if (type == "connection") {
        sendConnection();
    }
    else if (type == "relay_state") {
        sendRelayState();
    }
    else if (type == "datetime") {
        sendDateTime();
    }
    else if (type == "config") {
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

}

