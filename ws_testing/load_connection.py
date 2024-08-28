import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# websocketURL = "ws://192.168.4.1:5555/ws"
websocketURL = "ws://192.168.5.70:5555/ws"

def main():
    with connect(websocketURL) as websocket:
        print("Testing ESP32 websockets load connection")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")

if __name__ == "__main__":
    main()