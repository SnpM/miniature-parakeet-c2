# Miniature Parakeet C2
## Design

executor: interfaces with OS to execute shell commands
networker: all low-level socket stuff; gets messages from point A to point B
server: listens for a client; when connected, drops into a bash shell on the client
client: connects to hardcoded server IP; waits for messages and executes stuff


## C Project


## Resources

Example of I'm learning to do: https://github.com/17Chad/Phantom-C2/