from src.server import Server
from tests.utils import DummyServerNetworker
import io
import pytest
from time import sleep

def test_send_command(capsys):
    server = Server(DummyServerNetworker())
    server.start()
    crib = "ilguwbg iueoitheiotbqriu"
    
    server.send_command(f"echo {crib}")
    
    sleep(.1)
    
    server.send_command("leave")
    sleep(.1)
    captured = capsys.readouterr().out.strip()
    cribs = set([crib,"bye"])
    
    for item in cribs:
        assert item in captured

def test_cli(capsys, monkeypatch):
    server = Server(DummyServerNetworker())

    crib = "ilguwbg iubqriu"
    stdin = f"echo {crib}\nleave"

    server.start()    
    
    monkeypatch.setattr('sys.stdin', io.StringIO(stdin))
    server.cli()
    captured = capsys.readouterr().out.strip()
    
    cribs = set([crib,"bye"])
    
    for item in cribs:
        assert item in captured
                    
