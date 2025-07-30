
#ifndef NETWORKER_H
#define NETWORKER_H

#include <stdio.h>
#include <sys/socket.h> 

typedef struct {

} NetworkServer;

typedef struct {
} NetworkClient;

NetworkServer networker_host(const char ip[], int port);

NetworkClient networker_connect(const char ip[], int port);

int send_client2server(const char message[]);

int send_server2client(const char message[]);

#endif