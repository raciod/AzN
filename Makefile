CC     = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC    = main.c src/sender.c src/receiver.c src/header.c
OBJ    = $(SRC:.c=.o)

NAME   = main

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(NAME)
