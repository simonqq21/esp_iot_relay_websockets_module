import asyncio
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

# websocketURL = "ws://192.168.4.1:5555/ws"
websocketURL = "ws://192.168.5.70:5555/ws"

def main():
    with connect(websocketURL) as websocket:
        print("Testing ESP32 websockets save config")
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
        print("Saved config to ESP32.")

if __name__ == "__main__":
    main()
    



# import asyncio
# from websockets.sync.client import connect
# from time import sleep 
# import json 
# from datetime import datetime, time

# # websocketURL = "ws://192.168.4.1:5555/ws"
# websocketURL = "ws://192.168.5.70:5555/ws"

# def main():
#     with connect(websocketURL) as websocket:
#         print("Testing ESP32 websockets save config")
        

# if __name__ == "__main__":
#     main()
