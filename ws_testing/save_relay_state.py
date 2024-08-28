import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# websocketURL = "ws://192.168.4.1:5555/ws"
websocketURL = "ws://192.168.5.70:5555/ws"

def main():
    with connect(websocketURL) as websocket:
        print("Testing ESP32 websockets save relay_state")
        data = {}
        data["cmd"] = "save"
        data["type"] = "relay_state"
        data["payload"] = {}
        data["payload"]["relay_state"] = True
        websocket.send(json.dumps(data))
        print("Saved relay_state to ESP32.")

if __name__ == "__main__":
    main()