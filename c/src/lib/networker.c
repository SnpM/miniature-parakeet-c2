#include "networker.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

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
    socklen_t addrlen = sizeof(address); //why tf does accept() require a reference?!?!?


    //bind server
    int bind_result = bind(server_fd, (struct sockaddr *) &address, sizeof(address));
    if (bind_result < 0)
    {
        perror("bind bad");
        exit(EXIT_FAILURE);
    }

    //listen
    printf("Listening on %s:%d\n", ip, port);
    int listen_status = listen(server_fd, 3);
    if (listen_status < 0) {
        perror("listen bad");
        exit(EXIT_FAILURE);
    }

    int client_fd = accept(server_fd, (struct sockaddr *) &address, &addrlen);
    if (client_fd < 0)  {
        perror("connect bad");
        exit(EXIT_FAILURE);
    }

    printf("server: client connected\n");
}

NetworkClient networker_connect(const char ip[], int port) {
    // make socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        perror("create socket no bueno");
        exit(EXIT_FAILURE);
    }

    //build address
    struct sockaddr_in serv_address; 
    serv_address.sin_addr.s_addr = inet_addr(ip);
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(port);

    printf("Connecting to %s:%d\n", ip, port);

    int connect_status = connect(client_fd, (struct sockaddr *) &serv_address, sizeof(serv_address));
    if (connect_status < 0){
        perror("connect bad");
        exit(EXIT_FAILURE);
    }
    printf("Client: connected");

}

int send_client2server(const char message[]) {
return 0;
}

int send_server2client(const char message[]){
return 0;
}