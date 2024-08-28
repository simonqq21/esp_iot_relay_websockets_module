import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

websocketURL = "ws://192.168.4.1:5555/ws"
# websocketURL = "ws://192.168.5.70:5555/ws"
correct = True
# correct = False

if (correct):
    data = {}
    data["cmd"] = "save"
    data["type"] = "connection"
    data["payload"] = {}
    data["payload"]["ssid"] = "QUE-STARLINK"
    data["payload"]["pass"] = "Quefamily01259"
    data["payload"]["ipIndex"] = 70
    data["payload"]["port"] = 5555
else:
    data = {}
    data["cmd"] = "save"
    data["type"] = "connection"
    data["payload"] = {}
    data["payload"]["ssid"] = "QUE-STARLINK"
    data["payload"]["pass"] = "afafafafa"
    data["payload"]["ipIndex"] = 70
    data["payload"]["port"] = 5555

# test script for the websocket module 
def main():
    with connect(websocketURL) as websocket:
        # save connection
        websocket.send(json.dumps(data))

if __name__ == "__main__":
    main()