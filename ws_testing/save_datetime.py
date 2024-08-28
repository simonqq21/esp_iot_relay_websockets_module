import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# websocketURL = "ws://192.168.4.1:5555/ws"
websocketURL = "ws://192.168.5.70:5555/ws"

def main():
    with connect(websocketURL) as websocket:
        print("Testing ESP32 websockets save datetime")
        data = {}
        data["cmd"] = "save"
        data["type"] = "datetime"
        data["payload"] = {}
        data["payload"]["datetime"] = datetime.now().isoformat()
        websocket.send(json.dumps(data))
        print("Saved datetime to ESP32.")

if __name__ == "__main__":
    main()