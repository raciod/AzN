#ifndef RECEIVER_H
#define RECEIVER_H

#define PORT "5001"

int receiver_listen(int *socket_client);
void receiver_recieve();

#endif
