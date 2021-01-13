# .DEFAULT_GOAL=all

CC=gcc
CFLAGS=-fsanitize=signed-integer-overflow -fsanitize=undefined -g -std=gnu99 -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

program: client.c server.c
	$(CC) -o client $(CFLAGS) client.c 
	$(CC) -o server $(CFLAGS) server.c 

clean:
	rm -rf $(CLIENT) $(SERVER)

