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
        String cmd = _jsonDoc["type"];
        Serial.printf("cmd=%s\n", cmd);
        
        if (cmd == "request") {
            Serial.printf("requested!");
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
void WebserverModule::sendConnectionDetails() {

}

void WebserverModule::sendRelayState() {

}

void WebserverModule::sendSystemDateTime() {

}

void WebserverModule::sendMainConfig() {

}


// method to handle requests from the client browser 
void WebserverModule::handleRequest() {

}


// methods to receive and set new state from client browser 
void WebserverModule::receiveConnectionDetails() {

}

void WebserverModule::receiveRelayState() {

}

void WebserverModule::receiveSystemDateTime() {

}

void WebserverModule::receiveMainConfig() {

}


