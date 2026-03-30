#include "include/receiver.h"
#include "include/sender.h"
#include "include/header.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
For now you need to give the file name and the file should be in the same directory as main, future support of path is comming

*/

int main(int argc, char *argv[])
{
    int fd; // the global fd
    // the header
    if (argc < 2) {
        fprintf(stderr, "Usage:\n"
                        "  Sender:   main -s [IP] [Path to file]\n"
                        "  Receiver: main -r  (Note: Run this first)\n");
        return 1;
    }
    if (strcmp(argv[1], "-r") == 0) {
        receiver_listen(&fd);
        receiver_recieve(&fd);
        close(fd);

    } else if (strcmp(argv[1], "-s") == 0) {
        sender_connect(&fd, argv[2]);
        sender_send(&fd, argv[3]);
        close(fd);

    } else if (strcmp(argv[1], "-h") == 0) {
        fprintf(stderr, "Usage:\n"
                        "  Sender:   main -s [IP] [Port] [Path to file]\n"
                        "  Receiver: main -r  (Note: Run this first)\n");
    } else {
        fprintf(stderr,
                "Undefined argument '%s'. Use -r, -s, or -h for help.\n",
                argv[1]);
        return 1;
    }

    return 0;
}
