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