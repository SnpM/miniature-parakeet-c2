from src.client import Client
from src.server import Server
from src.networker import Networker
from tests.utils import get_test_port
from time import sleep
def test_everythiiiing(capsys):
    port = get_test_port()
    server = Server(Networker(), port=port)
    with server:
        client = Client(Networker(), server_port=port)
        
        with client:
            server.start()
            client.start()
            
            crib = "moooooon"
            server.send_command(f"echo {crib}")
            
            sleep(.25)
            
            assert len(server.received_messages) == 1
            assert server.received_messages[-1].strip() == crib