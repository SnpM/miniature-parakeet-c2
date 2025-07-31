
#ifndef NETWORKER_H
#define NETWORKER_H

#include <stdio.h>
#include <sys/socket.h> 

typedef struct {
    int server_fd;
    int connection_fd;
} NetworkServer;

typedef struct {
    int client_fd;
} NetworkClient;

NetworkServer networker_host(const char ip[], int port);

NetworkClient networker_connect(const char ip[], int port);

int send_message(int socket_fd, char* message);

int network_poll(int socket_fd, char* message_out, int max_chars);
#endif