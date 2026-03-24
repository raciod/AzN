#include "../include/receiver.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



int receiver_listen(int *socket_client)
{
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    if(getaddrinfo(0, PORT, &hints, &bind_address)){
        fprintf(stderr, "getaddrinfo() failed.");
        return 1;
    }


    printf("Creating socket...\n");
    int socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    if(socket_listen < 0){
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        return 1;
    }

    printf("Binding socket to local address...\n");
    if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)){
        fprintf(stderr, "bind() failed. (%d)\n", errno);
        close(socket_listen);
        return 1;
    }    
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if(listen(socket_listen, 10) < 0){
        fprintf(stderr, "listen() failed. (%d)\n", errno);
        close(socket_listen);
        return 1;
    }

    printf("Waiting for connection...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    *socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
    if(*socket_client < 0){
        fprintf(stderr, "accept() failed. (%d)", errno);
        close(socket_listen);
        return 1;
    }
    
    printf("client is connected...\n");
    char address_buffer[100];
    getnameinfo((struct sockaddr*) &client_address, client_len, address_buffer, sizeof(address_buffer), 0,0,NI_NUMERICHOST);
    printf("%s\n", address_buffer);


    // printf("You are the receiver and you want to LISTEN.\n");
    return 0;
}
void receiver_recieve()
{
    printf("You are the receiver and you want to RECEIVE.\n");
}
