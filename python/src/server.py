from src.networker import NetworkerBase

from typing import final, List
import time
import datetime

@final
class Server:
    received_messages:List[str]
    
    def __init__(self, networker:NetworkerBase, ip:str="localhost", port:int=4000):
        self.networker = networker
        self.port = port
        self.ip=ip
        self.received_messages = []
        
    def handle_message(self, message:str):
        self.received_messages.append(message)
        print(message)
        
    def start(self):
        # Block thread and wait for client to connect
        self.networker.server_host(self.ip, self.port)
        
        # Client connected, do server stuff
        self.networker.register_message_handler(self.handle_message)
        
    def send_command(self,command:str):
        if command[-1] != '\n':
            command += "\n"
            
        if command.strip() == "leave":
            print ("bye")
            return False
        self.networker.send_message(command)
        return True
        
            
    def cli(self):
        print ("Client connected! Enter commands to execute...")
        while 1:
            command = input("> ")
            
            received_count = len(self.received_messages)
            send_time = time.time()

            if not self.send_command(command):
                break
            
            # Get response from client before sending another message
            WAIT_TIME = 5
            while(1):
                if len(self.received_messages) > received_count:
                    break
                if time.time() - send_time > WAIT_TIME:
                    print("Error: Last command timed out")
                    break

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.networker.close()

from src.networker import Networker
from src import config

if __name__ == "__main__":
    server = Server(
        Networker(),
        ip=config.SERVER_HOST_IP,
        port=config.SERVER_PORT
    )
    with server:
        server.start()
        print("Server started!")

        server.cli()