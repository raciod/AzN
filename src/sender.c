#include "../include/sender.h"

#include "../include/receiver.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Play the role of client
int sender_connect(int *socket_fd, const char *ip)
{
    // printf("You are the sender and you want to CONNECT.\n");
    // printf("fd: %d\n", *socket_fd);
    // printf("ip: %s\n", ip);
    // printf("port: %s\n", PORT);

    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(ip, PORT, &hints, &peer_address)) {
        fprintf(stderr, "getinfaddr() failed. (%d)", errno);
        return 1;
    }

    printf("Remote address is: \n");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen, address_buffer,
                sizeof(address_buffer), service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);

    printf("Creating socket...\n");
    *socket_fd = socket(peer_address->ai_family, peer_address->ai_socktype,
                        peer_address->ai_protocol);

    if (*socket_fd < 0) {
        fprintf(stderr, "socket() failed.(%d)\n", errno);
        return 1;
    }

    printf("Connecting...\n");
    if (connect(*socket_fd, peer_address->ai_addr, peer_address->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", errno);
        return 1;
    }
    freeaddrinfo(peer_address);

    printf("Connected.\n");

    return 0;
}

int sender_send(int *socket_fd)
{
    char buffer[100];
    strncpy(buffer,
            "hi im the sender if you receive this message, you are connected",
            sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    printf("You are the sender and you want to SEND.\n");
    send(*socket_fd, buffer, strlen(buffer), 0);
    return 0;
}
