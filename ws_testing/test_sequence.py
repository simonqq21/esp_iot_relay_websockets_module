# connect to wifi

# load wifis
# load connection
# load datetime 
# load relay_state 
# load config

# save datetime
# load datetime to confirm the save
# save relay_state 
# load relay_state to confirm the save
# save config
# load config to confirm the save

# save relay_state to revert back 
# load relay_state to confirm the save
# save config to revert back 
# load config to confirm the save

# save connection with wrong wifi credentials to disconnect from the wifi 
#     and start the AP.


# start AP mode

# load wifis
# load connection
# load datetime 
# load relay_state 
# load config

# save datetime
# load datetime to confirm the save
# save relay_state 
# load relay_state to confirm the save
# save config
# load config to confirm the save

# save relay_state to revert back 
# load relay_state to confirm the save
# save config to revert back 
# load config to confirm the save

# save connection with wrong wifi credentials to stop the AP 
#     and reconnect to the wifi.

import asyncio
from websockets.asyncio.server import serve
from websockets.asyncio.client import connect
from time import sleep 
import json 
from datetime import datetime, time

class Client():
    def __init__(self, ip, port, wsRoute):
        self.ip = ip
        self.port = port
        self.wsRoute = wsRoute
        self.websocketURL = f"ws://{self.ip}:{self.port}/{self.wsRoute}"
    
    async def startWS(self):
        self.websocket = await connect(self.websocketURL)

    async def receiveWSMessages(self):
        while True:
            try:
                # with connect(self.websocketURL) as websocket:
                message = await self.websocket.recv()
                jsonmessage = json.loads(message)
                print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")
            except:
                pass

    async def loadWifis(self):
        print("Testing ESP32 websockets load wifis")
        # list wifis
        data = {}
        data["cmd"] = "request"
        data["type"] = "wifis"
        data["payload"] = {}
        websocket.send(json.dumps(data))

    async def loadConnection(self):
        print("load connection")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        await self.websocket.send(json.dumps(data))

    async def loadDateTime(self):
        print("Testing ESP32 websockets load datetime")
        data = {}
        data["cmd"] = "request"
        data["type"] = "datetime"
        data["payload"] = {}
        websocket.send(json.dumps(data))

    async def loadRelayState(self):
        print("Testing ESP32 websockets load relay_state")
        data = {}
        data["cmd"] = "request"
        data["type"] = "relay_state"
        data["payload"] = {}
        websocket.send(json.dumps(data))

    async def loadConfig(self):
        print("Testing ESP32 websockets load config")
        data = {}
        data["cmd"] = "request"
        data["type"] = "config"
        data["payload"] = {}
        websocket.send(json.dumps(data))

    async def saveConnection(self):
        data = {}
        data["cmd"] = "save"
        data["type"] = "connection"
        data["payload"] = {}
        data["payload"]["ssid"] = "QUE-STARLINK"
        data["payload"]["pass"] = "Quefamily01259"
        data["payload"]["ipIndex"] = 70
        data["payload"]["port"] = 5555
        # save connection
        websocket.send(json.dumps(data))

    async def saveDateTime(self):
        print("Testing ESP32 websockets save datetime")
        data = {}
        data["cmd"] = "save"
        data["type"] = "datetime"
        data["payload"] = {}
        data["payload"]["datetime"] = datetime.now().isoformat()
        websocket.send(json.dumps(data))
        print("Saved datetime to ESP32.")

    async def saveRelayState(self):
        print("Testing ESP32 websockets save relay_state")
        data = {}
        data["cmd"] = "save"
        data["type"] = "relay_state"
        data["payload"] = {}
        data["payload"]["relay_state"] = True
        websocket.send(json.dumps(data))
        print("Saved relay_state to ESP32.")

    async def saveConfig(self):
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

async def testSequence(client):
    await client.loadConnection()

async def main():
    client = Client("192.168.5.70", 5555, "ws")
    await client.startWS()
    # task1 = asyncio.create_task(func1())
    receiveMessageTask = asyncio.create_task(client.receiveWSMessages())
    testSequenceTask = asyncio.create_task(testSequence(client))
    await asyncio.gather(receiveMessageTask, testSequenceTask)

if __name__ == "__main__":
    asyncio.run(main())