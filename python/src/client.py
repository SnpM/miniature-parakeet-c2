from src.networker import NetworkerBase
from src.executor import execute

class Client:
    def __init__(self, networker:NetworkerBase, server_ip:str="localhost", server_port:int=4000):
        self.networker = networker
        self.server_ip = server_ip
        self.server_port = server_port
        
    def handle_message(self,message):
        output = execute(message)
        self.networker.send_message(output)
        
    def start(self):
        self.networker.client_connect(self.server_ip, self.server_port)
        self.networker.register_message_handler(self.handle_message)
        
    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.networker.close()
        

from src.networker import Networker
from src import config

if __name__ == "__main__":

    client = Client(
        Networker(),
        server_ip=config.SERVER_IP,
        server_port=config.SERVER_PORT
    )
    with client:
        client.start()
        