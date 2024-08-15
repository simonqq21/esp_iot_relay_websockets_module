import asyncio
from websockets.sync.client import connect
from time import sleep 

def main():
    with connect("ws://192.168.5.70:5555/ws") as websocket:
        websocket.send('{"cmd": "save", "type": "datetime", "payload": {"datetime": "2024-01-01T10:00:00Z"}}')
        # message = websocket.recv()
        # print(f"message = {message}")

        websocket.send('{"cmd": "request", "type": "connection", "payload": {}}')
        message = websocket.recv()
        print(f"message = {message}")
        sleep(3)
        websocket.send('{"cmd": "request", "type": "datetime", "payload": {}}')
        message = websocket.recv()
        print(f"message = {message}")

if __name__ == "__main__":
    main()