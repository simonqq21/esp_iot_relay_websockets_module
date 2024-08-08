#include "Webserver_module.h"

WebserverModule::WebserverModule(): _server(5555), _ws("/ws") {

}

void WebserverModule::begin() {

}

void WebserverModule::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {

}

void WebserverModule::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
    void *arg, uint8_t *data, size_t len) {

}



