# AzN

Peer-to-peer file and text sharing over raw TCP sockets for Unix/Linux.

## Usage

```bash
# Receiver (run first)
./main -r

# Sender
./main -s [IP] [text or filepath]
```

to test it localy:
```bash
# Receiver (run first)
./main -r

# Sender
./main -s 127.0.0.1 testfile.txt
```
## Project Structure

```
AzN/
├── src/
│   ├── sender.c     — creates the socket, connects to the target IP, orchestrates the send flow
│   ├── receiver.c   — binds to the port, listens for incoming connections, orchestrates the receive flow
│   └── header.c     — builds the header string before sending and parses it back on the receiver side
├── include/
│   ├── sender.h
│   ├── receiver.h
│   └── header.h
├── main.c           — entry point, parses -s or -r flag, dispatches to sender or receiver
├── Makefile
└── README.md
```

## Functions

**main.c**
- `main()` — parse argv, dispatch to sender or receiver

**sender.c**
- `sender_connect()` — create socket and connect to target IP:port
- `sender_send()` — build header then fread/send loop for file or text

**receiver.c**
- `receiver_listen()` — bind, listen, accept incoming connection
- `receiver_receive()` — parse header then recv/fwrite loop for file or text

**header.c**
- `header_build()` — construct the `TYPE/NAME/SIZE` header string
- `header_parse()` — read from socket line by line until blank line, fill a header struct

## TODO

- [ ] get the file from the user check if it exist detemine its size and divid it and send it to the receiver
