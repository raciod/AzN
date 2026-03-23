# AzN

Peer-to-peer file and text sharing over raw TCP sockets for Unix/Linux.

## Usage

```bash
# Receiver (run first)
./main -r

# Sender
./main -s [IP] [text or filepath]
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

**Network & Sockets**
- [ ] create and bind a TCP socket in receiver
- [ ] connect to target IP:port in sender
- [ ] accept incoming connection in receiver
- [ ] close socket properly after transfer

**Header**
- [ ] define the header struct
- [ ] implement `header_build()`
- [ ] implement `header_parse()`

**Sender**
- [ ] detect if argument is a file path or plain text
- [ ] send header
- [ ] send text over socket
- [ ] send file in chunks with fread/send loop

**Receiver**
- [ ] receive and parse header
- [ ] receive text and print to terminal
- [ ] receive file and write to disk in binary mode

**CLI**
- [ ] parse `-s [IP] [text/file]` in main
- [ ] parse `-r` in main
- [ ] handle wrong usage and print a usage message

**Testing**
- [ ] test text transfer on localhost
- [ ] test small file transfer
- [ ] test large file transfer
- [ ] test different file formats (pdf, image, video)
