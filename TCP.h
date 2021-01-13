#ifndef TCP_H_
#define TCP_H_



#define CMD_LENGTH 256
#define ARGS_LENGTH 256
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

typedef struct tcp_info{
    char host[20];
    uint16_t port;
    int sockFd;
} tcp_info;



typedef struct message_t {
    char cmd[CMD_LENGTH];
    char args[ARGS_LENGTH];
} message_t;



#endif 