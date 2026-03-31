#include "../include/transfer.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>

int transfer_send(int *socket_fd, FILE *fptr)
{
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fptr)) > 0)
    {
        send(*socket_fd, buffer, bytes_read, 0);
    }
    fclose(fptr);
    return 0;
}

int transfer_recv(int *socket_fd, long size, char name[])
{
    char recv_name[256];
    snprintf(recv_name, sizeof(recv_name), "recv-%s", name);
    FILE *fptr = fopen(recv_name, "wb");
    if (fptr == NULL) {
        fprintf(stderr, "fopen() failed. (%d)\n", errno);
        return 1;
    }
    char buffer[4096];
    long remaining = size;
    while (remaining > 0)
    {
        size_t to_read = remaining < 4096 ? remaining : 4096;
        ssize_t bytes_recv = recv(*socket_fd, buffer, to_read, 0);
        if (bytes_recv <= 0)
            break;
        fwrite(buffer, 1, bytes_recv, fptr);
        remaining -= bytes_recv;
    }
    fclose(fptr);
    return 0;
}
