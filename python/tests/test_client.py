from tests.utils import DummyClientNetworker
from src.client import Client
from typing import cast, List

def test_everything():
    client = Client(DummyClientNetworker(), "")
    client.start()
    
    crib = "ltiuhw whatever"
    client.networker.receive_message("echo " + crib)
    networker:DummyClientNetworker = cast(DummyClientNetworker, client.networker)
    sent_messages:List[str] = networker.sent_messages
    
    print(sent_messages)
    assert any([(crib in message) for message in sent_messages])