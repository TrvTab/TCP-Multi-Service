

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "TCP.h"


#define BUFFER   512

int create_Socket(int *socketfd){
  *socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*socketfd < 0) {
    perror("Socket Creation Failure\n");
    return -1;
  }
  return *socketfd;

}

tcp_info connectToSocket(const char *host, uint16_t port, int sockfd) {
  struct sockaddr_in server_add = {0};

  // create a new socket
  create_Socket(&sockfd);

  // connect to server
  server_add.sin_family = AF_INET;
  server_add.sin_addr.s_addr = inet_addr(host);
  server_add.sin_port = htons(port);

  if (connect(sockfd, (struct sockaddr *)&server_add, sizeof(struct sockaddr_in)) < 0) {
    perror("Connection Failure\n");
    exit(1);
  }

  tcp_info backend;
  strcpy(backend.host, host);
  backend.port = port;
  backend.sockFd = sockfd;
  return backend;
}

message_t parse_line(char input[]){
    char* command = strtok(input, " ");
    char* arguments = strtok(NULL, "");
    message_t msg;

    strcpy(msg.cmd, command);
    if (arguments == NULL){
        strcpy(msg.args, "");
    } else{
     strcpy(msg.args, arguments);
    }
    return msg;
    
}


int main(int argc, char *argv[]){

   if (argc != 3) {
        perror("Must input address and port\n");
        return -1;
   }

  int sockfd;
  char input[BUFFER] = {0};
  char result[BUFFER] = {0};
  
  
  //Connect to server and initialize tcp_info value
  tcp_info backend = connectToSocket(argv[1], (uint16_t) atoi(argv[2]), sockfd);

  
   while(1){
     // clear buffers
    memset(input, 0, sizeof(input));
    memset(result, 0, sizeof(result));
    // get user input
    fgets(input, BUFFER, stdin);
    //parse user input into message struct
    message_t msg = parse_line(input);
    // if the user inputs exit then shutdown frontend
    if ((strcmp(msg.cmd, "exit\n")) == 0){
      shutdown(backend.sockFd, 2);
    }
    // if user presses enter, do nothing
    if ((strcmp(msg.cmd, "\n")) == 0){
      continue;
    }
    // Pass user input to server
     send(backend.sockFd,(char*) &msg, sizeof(msg), 0);
    // receive and check if recv functioned properly
    ssize_t received = recv(sockfd, result, sizeof(result), 0);
    if (received <= 0) {
      break;
    }
    // print result returned from server and if it is Bye then dont put result in front of it
      printf("Result : %s\n", result);
    
  }

  return 0;
}
