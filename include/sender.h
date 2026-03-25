#ifndef SENDER_H
#define SENDER_H

int sender_connect(int *socket_fd, const char *ip);
int sender_send(int *socket_fd, char *file);

#endif
