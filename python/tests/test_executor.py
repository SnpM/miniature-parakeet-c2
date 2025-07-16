import pytest
import src
import src.executor


def test_execute():
    crib = "aoautha slekgnals"
    assert crib == src.executor.execute("echo "+crib).strip()