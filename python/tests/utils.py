from src.networker import NetworkerBase, MessageHandler
import os
from typing import List

from threading import Lock
port_counter_lock:Lock = Lock()
port_counter = 12000
def get_test_port()->int:
    global port_counter
    with port_counter_lock:
        port = port_counter 
        port_counter += 1
    return port


class DummyServerNetworker(NetworkerBase):
    
    def __init__(self):
        super().__init__()
    
    
    def server_host(self,server_ip:str, server_port:int):
        """Host the server"""
        pass

    def client_connect(self,server_ip:str, server_port:int):
        """Connect to server from client"""
        pass

    def send_message(self,message:str):
        """Send message from client - server (and vice versa)"""
        p = os.popen(message)
        output:str = p.read()
        
        self.receive_message(output)
    
class DummyClientNetworker(NetworkerBase):
    def __init__(self):
        super().__init__()
        self.sent_messages:List[str] = []
    
    def server_host(self,server_ip:str, server_port:int):
        """Host the server"""
        pass

    def client_connect(self,server_ip:str, server_port:int):
        """Connect to server from client"""
        pass

    def send_message(self,message:str):
        """Send message from client - server (and vice versa)"""
        self.sent_messages.append(message)
