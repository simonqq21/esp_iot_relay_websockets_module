import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# test script for the websocket module 
def main():
    with connect("ws://192.168.5.70:5555/ws") as websocket:
        print("Testing ESP32 websockets loading data")
        sleep(5)

        print("Test load connection info from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test load system datetime from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "datetime"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        # print(f"message = {message}")
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test load relay status from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "relay_state"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test load timing configuration from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "config"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Testing ESP32 websockets saving data")
        sleep(5)
        
        print("Test save connection info to ESP32")
        data = {}
        data["cmd"] = "save"
        data["type"] = "connection"
        data["payload"] = {}
        data["payload"]["ssid"] = "basil"
        data["payload"]["pass"] = "p@ssw0rd123"
        data["payload"]["ip"] = "192.168.5.71"
        data["payload"]["port"] = 5556
        websocket.send(json.dumps(data))
        print("Saved data to ESP32.")
        print("Loading saved connection info from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test save relay state to ESP32")
        data = {}
        data["cmd"] = "save"
        data["type"] = "relay_state"
        data["payload"] = {}
        data["payload"]["relay_state"] = True
        websocket.send(json.dumps(data))
        print("Saved data to ESP32.")
        print("Loading saved relay state from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "relay_state"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test save datetime info to ESP32")
        data = {}
        data["cmd"] = "save"
        data["type"] = "datetime"
        data["payload"] = {}
        data["payload"]["datetime"] = datetime.now().isoformat()
        websocket.send(json.dumps(data))
        print("Saved data to ESP32.")
        print("Loading saved datetime info from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "datetime"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

        print("Test save configuration info to ESP32")
        data = {}
        data["cmd"] = "save"
        data["type"] = "config"
        data["payload"] = {}
        data["payload"]["name"] = "basil_ESP32"
        data["payload"]["ntpEnabledSetting"] = True 
        data["payload"]["gmtOffsetSetting"] = 8
        data["payload"]["timerEnabledSetting"] = True
        data["payload"]["ledSetting"] = 1
        data["payload"]["timeSlots"] = []
        timeslot_times = [{"onStartTime": time(6,0,0),
                           "onEndTime": time(6,0,30)}, 
                           {"onStartTime": time(12,0,0),
                           "onEndTime": time(14,0,0)}, 
                           {"onStartTime": time(18,0,0),
                           "onEndTime": time(21,0,0)}, ]
        for i in range(3):
            timeslot = {}
            timeslot["index"] = i 
            timeslot["enabled"] = True 
            timeslot["onStartTime"] = timeslot_times[i]["onStartTime"].isoformat()
            timeslot["onEndTime"] = timeslot_times[i]["onEndTime"].isoformat()
            data["payload"]["timeSlots"].append(timeslot)

        websocket.send(json.dumps(data))
        print("Saved data to ESP32.")
        print("Loading saved configuration info from ESP32")
        data = {}
        data["cmd"] = "request"
        data["type"] = "config"
        data["payload"] = {}
        websocket.send(json.dumps(data))
        message = websocket.recv()
        jsonmessage = json.loads(message)
        print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
        sleep(3)

if __name__ == "__main__":
    main()