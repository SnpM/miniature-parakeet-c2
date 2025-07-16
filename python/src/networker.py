from abc import ABC, abstractmethod
from typing import Callable
import socket
import threading
from typing import List, Optional

MessageHandler = Callable[[str], None] 

class NetworkerBase(ABC):
    
    def __init__(self):
        self.message_handlers:List[MessageHandler] = []
        
    @abstractmethod
    def server_host(self,server_ip:str="localhost",server_port:int=4000):
        """Host the server"""
        raise NotImplementedError()

    @abstractmethod
    def client_connect(self,server_ip:str="localhost", server_port:int=4000):
        """Connect to server from client"""
        raise NotImplementedError()

    @abstractmethod
    def send_message(self,message:str):
        """Send message from client - server (and vice versa)"""
        raise NotImplementedError
    
    def receive_message(self,message:str):
        for handler in self.message_handlers:
            handler(message)
        
    def register_message_handler(self, func:MessageHandler):
        """Register a function for handling received messages"""
        self.message_handlers.append(func)
    
    def close(self):
        pass
    
from queue import Queue
from time import sleep
import fcntl
import os

class Networker(NetworkerBase):
    def __init__(self):
        super().__init__()
        self.send_queue:List[str] = []
        self.receive_queue:List[str] = []
        self.mode = "unknown"
        self.tick_thread:Optional[threading.Thread] = None
        self.__running = True
        
    def socket_tick(self, conn:socket.socket):
        DELIMITER = "<<hi i am an delimiter. we can put tags and stuff here. >>"
        fcntl.fcntl(conn, fcntl.F_SETFL, os.O_NONBLOCK)

        while True:          
            if not self.__running:
                break  
            try:
                data = conn.recv(1024)
            except socket.error as e: # type: ignore
                err = e.args[0]
                import errno
                if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                    pass
                else:
                    print(e)
                    pass
            else:
                
                # store in queue
                for byte in data:
                    self.receive_queue.append(chr(byte))
                    

                # find new line indicating full command
                def process_next_message():
                    receive_queue_str = ''.join(self.receive_queue)
                    
                    delim_position = receive_queue_str.index(DELIMITER)
                    delim_end = delim_position + len(DELIMITER)
                    
                    message = receive_queue_str[0:delim_position]
                    print(message)
                    self.receive_message(''.join(message))
                    self.receive_queue = self.receive_queue[delim_end+1::]
                    if len(self.receive_queue) > 0:
                        process_next_message()
                        
                process_next_message()

            if len(self.send_queue) > 0:
                
                for message in self.send_queue:
                    message = message + DELIMITER
                    encoded = message.encode()
                    conn.sendall(encoded)
                    print("sent")
                    
                self.send_queue = []
            sleep(.05)
 
        
    def server_host(self,server_ip:str="localhost",server_port:int=4000):
        # TODO guard against multiple connect/host calls
        
        HOST = server_ip
        PORT = server_port
        self.mode = "server"

        def host():
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.bind((HOST, PORT))
                s.listen(1)
                conn, addr = s.accept()
                with conn:
                    result = self.socket_tick(conn)
                        
        self.tick_thread = threading.Thread(target=host)
        self.tick_thread.start()
        
    def client_connect(self,server_ip:str="localhost", server_port:int=4000):
        # TODO guard against multiple connect/host calls
        
        HOST = server_ip
        PORT = server_port
        self.mode = "client"
        
        def connect():
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((HOST, PORT))
                self.socket_tick(s)
        self.tick_thread = threading.Thread(target=connect)
        self.tick_thread.start()
        
    def send_message(self,message:str):
        """Send message from client - server (and vice versa)"""
        self.send_queue.append(message)
        
    def close(self):
        self.__running = False