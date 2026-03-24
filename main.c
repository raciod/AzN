#include "include/receiver.h"
#include "include/sender.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage:\n"
                        "  Sender:   main -s [IP] [Port] [Path to file]\n"
                        "  Receiver: main -r  (Note: Run this first)\n");
    }
    if (strcmp(argv[1], "-r") == 0) {
        receiver_listen();
        receiver_recieve();

    } else if (strcmp(argv[1], "-s") == 0) {
        sender_connect();
        sender_send();
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
