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
        

    async def loadConnection(self):
        print("load connection")
        data = {}
        data["cmd"] = "request"
        data["type"] = "connection"
        data["payload"] = {}
        await self.websocket.send(json.dumps(data))

    async def loadDateTime(self):

    async def loadRelayState(self):

    async def loadConfig(self):

    async def saveConnection(self):

    async def saveDateTime(self):

    async def saveRelayState(self):

    async def saveConfig(self):


async def main():
    client = Client("192.168.5.70", 5555, "ws")
    await client.startWS()
    # task1 = asyncio.create_task(func1())
    task1 = asyncio.create_task(client.receiveWSMessages())
    task2 = asyncio.create_task(client.load_wifis())
    await asyncio.gather(task2, task1)
    # loop = asyncio.get_event_loop()
    # loop.run_until_complete(asyncio.gather(task1, task2))

if __name__ == "__main__":
    asyncio.run(main())