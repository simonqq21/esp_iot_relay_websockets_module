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
from websockets.sync.client import connect
from time import sleep 
import json 
from datetime import datetime, time

class Client():
    def __init__(self, ip, port, wsRoute):
        self.ip = ip
        self.port = port
        self.wsRoute = wsRoute
        self.websocketURL = f"ws://{self.ip}:{self.port}/{self.wsRoute}"
    
    async def receiveWSMessages(self, websocket):
        async for message in websocket:
            print(f"received from ESP32: {message}")

    async def serveWS(self, *tasks):
        async with serve(self.receiveWSMessages, self.ip, self.port, self.wsRoute):
            await asyncio.gather(*tasks, asyncio.get_running_loop().create_future())

    async def load_wifis(self):
        with connect(self.websocketURL)as websocket:
            print("Testing ESP32 websockets load connection")
            data = {}
            data["cmd"] = "request"
            data["type"] = "connection"
            data["payload"] = {}
            websocket.send(json.dumps(data))
            message = websocket.recv()
            jsonmessage = json.loads(message)
            print(f"JSON message = {json.dumps(jsonmessage, indent=True)}\n")

async def main():
    client = Client("192.168.5.70", 5555, "ws")
    task1 = asyncio.create_task(client.receiveWSMessages())
    await asyncio.gather(task1)

if __name__ == "__main__":
    asyncio.run(main())