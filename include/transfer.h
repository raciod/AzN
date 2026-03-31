#ifndef TRANSFER_H
# define TRANSFER_H
#include <stdio.h>

int transfer_send(int *socket_fd, FILE *fptr);
int transfer_recv(int *socket_fd, long size, char name[]);

#endif
