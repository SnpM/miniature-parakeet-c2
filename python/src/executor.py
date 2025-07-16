import os

def execute(command:str)-> str:
    """executes a command and returns the string output"""
    # https://stackoverflow.com/questions/89228/how-do-i-execute-a-program-or-call-a-system-command
    p = os.popen(command)
    
    output = p.read()
    return output