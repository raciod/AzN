#include "../include/receiver.h"
#include "../include/header.h"
#include "../include/transfer.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Play the role of the server
int receiver_listen(int *socket_client)
{
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    struct addrinfo *bind_address;
    if (getaddrinfo(0, PORT, &hints, &bind_address)) {
        fprintf(stderr, "getaddrinfo() failed.");
        return 1;
    }

    printf("Creating socket...\n");
    int socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                           bind_address->ai_protocol);
    if (socket_listen < 0) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        return 1;
    }

    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", errno);
        close(socket_listen);
        return 1;
    }
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", errno);
        close(socket_listen);
        return 1;
    }

    printf("Waiting for connection...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    *socket_client =
        accept(socket_listen, (struct sockaddr *)&client_address, &client_len);
    if (*socket_client < 0) {
        fprintf(stderr, "accept() failed. (%d)", errno);
        close(socket_listen);
        return 1;
    }
    close(socket_listen);

    printf("client is connected...\n");
    char address_buffer[100];
    getnameinfo((struct sockaddr *)&client_address, client_len, address_buffer,
                sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    printf("%s\n", address_buffer);

    return 0;
}
int receiver_recieve(int *socket_client)
{
    printf("Reading header...\n");
    char header_buffer[1024];
    int byte_received = recv(*socket_client, header_buffer, 1024, 0);
    header_buffer[byte_received] = '\0';

    // Parsing the recieved request
    t_header v_header;
    // char *header, t_header *v_header
    header_parse(header_buffer,&v_header);

    printf("header[receiver_receive()] : if you see this this mean that you send the header and parse it successfuly.\n");
    printf("Type: %s\n", v_header.type);
    printf("Name: %s\n", v_header.name);
    printf("Size: %ld\n", v_header.size);

    // receving the rest of the file 
    printf("Reading body...\n");
    transfer_recv(socket_client, v_header.size, v_header.name);
    



    return 0;
}
