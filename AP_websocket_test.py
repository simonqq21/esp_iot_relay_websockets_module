import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# test script for the websocket module 
def main():
    with connect("ws://192.168.4.1:5555/ws") as websocket:
        print("Testing ESP32 websockets loading data")

        # list wifis
        data = {}
        data["cmd"] = "request"
        data["type"] = "wifis"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")

        print("Test load connection info from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")

        # save correct connection
        data = {}
        data["cmd"] = "save"
        data["type"] = "connection"
        data["payload"] = {}
        data["payload"]["ssid"] = "QUE-STARLINK"
        data["payload"]["pass"] = "Quefamily01259"
        data["payload"]["ipIndex"] = 70
        data["payload"]["port"] = 5555
        websocket.send(json.dumps(data))

        # # save wrong connection
        # data = {}
        # data["cmd"] = "save"
        # data["type"] = "connection"
        # data["payload"] = {}
        # data["payload"]["ssid"] = "QUE-STARLINK"
        # data["payload"]["pass"] = "afafafa"
        # data["payload"]["ipIndex"] = 70
        # data["payload"]["port"] = 5555
        # websocket.send(json.dumps(data))

if __name__ == "__main__":
    main()