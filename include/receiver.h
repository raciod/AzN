#ifndef RECEIVER_H
#define RECEIVER_H

#define PORT "49152"

int receiver_listen(int *socket_client);
int receiver_recieve(int *socket_client);

#endif
