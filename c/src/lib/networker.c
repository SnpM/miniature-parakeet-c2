#include "networker.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <poll.h>
// https://www.geeksforgeeks.org/c/socket-programming-cc/#

NetworkServer networker_host(const char ip[], int port)
{
    // make socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("create socket no bueno");
        exit(EXIT_FAILURE);
    }

    // build address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    socklen_t addrlen = sizeof(address); // why tf does accept() require a reference?!?!?

    // bind server
    int bind_result = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (bind_result < 0)
    {
        perror("bind bad");
        exit(EXIT_FAILURE);
    }

    // listen
    printf("Listening on %s:%d\n", ip, port);
    int listen_status = listen(server_fd, 3);
    if (listen_status < 0)
    {
        perror("listen bad");
        exit(EXIT_FAILURE);
    }

    int connection_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (connection_fd < 0)
    {
        perror("connect bad");
        exit(EXIT_FAILURE);
    }



    printf("server: client connected\n");

    NetworkServer network_server;
    network_server.server_fd = server_fd;
    network_server.connection_fd = connection_fd;
    return network_server;
}

//stateless function to poll socket for received message
//Returns number of bytes received or 0 for no data received
int network_poll(int socket_fd, char* message_out, int max_chars){
    // We're gonna use a non-blocking poll instead of blocking select() strategy
    // https://linux.die.net/man/2/fcntl
    fcntl(socket_fd, F_SETLK, O_NONBLOCK);

    // https://www.reddit.com/r/C_Programming/comments/eeqi8r/understanding_how_to_use_poll_in_socket/
    struct pollfd poll_fd;
    poll_fd.events = POLLIN;
    poll_fd.fd = socket_fd;

    //poll 1 socket and immediately return
    int poll_result = poll(&poll_fd, 1, 0);
    if (poll_result < 0) {
        perror("ERROR: poll bad");
        exit(EXIT_FAILURE);
    }

    if (poll_result == 0) {
        //no data, just return 0
        return 0;
    }
    
    //data received
    //ensure we get POLLIN event
    if (!(poll_fd.revents & POLLIN)) {
        perror("ERROR: unexpected poll event");
    }

    char buffer[0x1000];

    //parse the message
    ssize_t numbytes = recv(socket_fd, buffer, sizeof(buffer), 0);
    if (numbytes < 0) {
        perror("ERROR: failed recv");
        exit(EXIT_FAILURE);
    }
    if (numbytes > 0) {
        printf("Received %li bytes!", (long)numbytes);

        strncpy(message_out, buffer, max_chars+1);
        if (strlen(buffer) > max_chars) {
            printf("Warning: received %li bytes greater than %d max_chars", numbytes, max_chars);
        }
        return numbytes;
    }
    else {
        perror("pika????");
        exit(EXIT_FAILURE);
    }


}

NetworkClient networker_connect(const char ip[], int port)
{
    // make socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        perror("create socket no bueno");
        exit(EXIT_FAILURE);
    }

    // build address
    struct sockaddr_in serv_address;
    serv_address.sin_addr.s_addr = inet_addr(ip);
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(port);

    printf("Connecting to %s:%d\n", ip, port);

    int connect_status = connect(client_fd, (struct sockaddr *)&serv_address, sizeof(serv_address));
    if (connect_status < 0)
    {
        perror("connect bad");
        exit(EXIT_FAILURE);
    }
    printf("Client: connected");

    NetworkClient network_client;
    network_client.client_fd = client_fd;
    return network_client;
}

int send_message(int socket_fd, char* message)
{
    send(socket_fd, &message, sizeof(message), 0);
}