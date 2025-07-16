from src.networker import Networker
from typing import List
from time import sleep
import pytest
from tests.utils import get_test_port

from collections import namedtuple

ClientServer = namedtuple('ClientServer', ['client','server','client_messages','server_messages'])


@pytest.fixture
def client_server():
    # We need to get our port atomically
    port = get_test_port()

    # setup server
    server_message_stack:List[str] = []
    def handle_server_message(message):
        server_message_stack.append(message)
        
    server = Networker()
    server.server_host(server_port=port)
    server.register_message_handler(handle_server_message)
    
    sleep(.2)
    
    # setup client
    client_message_stack:List[str] = []
    def handle_client_message(message):
        client_message_stack.append(message)
    client = Networker()
    client.client_connect(server_port=port)
    client.register_message_handler(handle_client_message)
    
    
    yield ClientServer(client,server,client_message_stack, server_message_stack) #type:ignore
    
    client.close()
    server.close()

def test_server2client(client_server:ClientServer):
    # test server -> client
    crib = "tiuethwuohet\n"
    client_server.server.send_message(crib)
    sleep(.1)
    assert len(client_server.client_messages) > 0
    assert client_server.client_messages[-1] == crib
    
def test_client2server(client_server:ClientServer):
    # test client -> server    
    crib = "iubjkerb\n"
    client_server.client.send_message(crib)
    sleep(.1)
    assert len(client_server.server_messages) > 0
    assert client_server.server_messages[-1] == crib
    
    