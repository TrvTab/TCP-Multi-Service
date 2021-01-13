
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#include "TCP.h"

#define BUFSIZE   1024




int addInts(int a , int b){
  return(a + b);
}

int multiply (int a, int b){
  return (a * b);
}

float divide(float a, float b){
  return (a / b);
}

uint64_t factorial (int x){
  uint64_t res = 1;
    for (int i = x; i >= 1; i--){
      res *= i;
  }
  return res;
}

int fibonnaci (int x){
  if (x <= 1){
    return x;
  }
  return fibonnaci(x-1) + fibonnaci(x-2);
}

float logarithm (float x, float base){
  return log(x) / log(base);
}
int create_Socket(int *socketfd){
  *socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*socketfd < 0) {
    perror("Socket Creation Failure\n");
    return -1;
  }
  return *socketfd;

}

int TCP_Func_Exec(int clientSockfd, message_t *received){
    char result[100];
    memset(result, 0, sizeof(result));

    // get individual arguments inputted in client
    char* arg1 = strtok(received->args, " ");
    char* arg2 = strtok(NULL, " ");

    // only one parameter inputted by user
    if (arg1 == NULL){
    if ((strcmp(received->cmd, "shutdown\n")) == 0){
        return 5;

    } else {
        sprintf(result, "There is no function %s found that takes no parameters", received->cmd);
    }

    // if one argument is inputted
    } else if (arg2 == NULL){
      if ((strcmp(received->cmd, "factorial"))== 0){
          uint64_t num_result = (factorial((uint64_t) (atoi(arg1))));
          sprintf(result, "%llu", num_result);

      } else if ((strcmp(received->cmd, "weather"))== 0){ 
        int weatherFound = 0;
        char line[200];
        
        char postalCode[30];
        char temp[10];
        memset(temp, '\0', sizeof(temp));
        strncpy(temp, arg1, 3);
        sprintf(postalCode, "%s\n" , temp);

        if (weatherFound == 0){
          char systemCommand[50];
          sprintf(systemCommand, "python weatherAPI.py %s", arg1);
          system(systemCommand);

          printf("System Command: %s", systemCommand);

          sleep(2);
          FILE* file = fopen("weatherDataFile.txt", "r");
          
          while (fgets(line, sizeof(line), file)) {
              if ((strcmp(postalCode, line)) == 0){
                weatherFound = 1;
                fgets(line, sizeof(line), file);
                strcpy(result, line);
                break;
            }

          }
          fclose(file);
        }

        else if ((strcmp(received->cmd, "fibonacci"))== 0){
          int fibAns = fibonnaci(atoi(arg1));
          sprintf(result, "%d", fibAns);
        }
          if (weatherFound == 0){
          sprintf(result, "Error Finding Weather");
        }
        
      }
      else{
        sprintf(result, "There is no function %s found that takes 1 parameter inputted in this manner", received->cmd);
      }

    
    // if two arguments are inputted
    } else {
      if ((strcmp(received->cmd, "add"))== 0){
        int num_result = addInts(atoi(arg1), atoi(arg2));
        // put sum into result to be sent to 
        sprintf(result, "%d", num_result);
          
    } else if ((strcmp(received->cmd, "multiply")) == 0){
        int num_result = multiply(atoi(arg1), atoi(arg2));
        sprintf(result, "%d" , num_result);

    } else if ((strcmp(received->cmd, "divide"))== 0){
        float num_result = divide(atof(arg1), atof(arg2));
        if (atof(arg2) == 0){
          sprintf(result, "Cannot do divison by zero");
        } else{
          sprintf(result, "%f", num_result);
        }

    } else if ((strcmp(received->cmd, "stats")) == 0){
      
        char line[200];
        int statsFound = 0;
        char statLine[30];
        sprintf(statLine, "%s %s", arg1, arg2);

        char systemCommand[50];
        sprintf(systemCommand, "python nhlStats.py %s %s", arg1, arg2);
        system(systemCommand);

        
        sleep(2);
        FILE* file = fopen("statsDataFile.txt", "r");
        while (fgets(line, sizeof(line), file)) {

          if ((strcmp(statLine, line)) == 0){
              statsFound = 1;
              fgets(line, sizeof(line), file);
              sprintf(result,"\n%s" ,line);
              fgets(line, sizeof(line), file);
              strcat(result, line);
              fgets(line, sizeof(line), file);
              strcat(result, line);
              fclose(file);
              break;
          }
        }
        if (statsFound == 0) {
          sprintf(result, "Error Finding Stats");
        }
        fclose(file);
    }
    else if ((strcmp(received->cmd, "log")) == 0){
      double logAns = logarithm(atof(arg1), atof(arg2));
      sprintf(result, "%f", logAns);
    }
    
    else{
      sprintf(result, "There is no function %s found that takes 2 parameters", received->cmd);
    }

    }
    send(clientSockfd, result, strlen(result), 0);
    return 0;

}

int main(int argc, char* argv[]) {
   if (argc != 3) {
        perror("Input address and port\n");
        return -1;
    }
  int sockfd;
  char msg[BUFSIZE];
  message_t* received;
  int cVal;
  

  // assign input to port and server address
  int port = atoi(argv[2]);
  char* host = argv[1];


 struct sockaddr_in server_address = {0};

 // creation of server

  // creation of socket
  create_Socket(&sockfd);

  // set socket options
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("Set Options Failure\n");
    return -1;
  }

  // bind to address and specified port
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(host);
  server_address.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("Binding Failure\n");
    return -1;
  }
  if (listen(sockfd, 8) < 0) {
    perror("Listen Failure\n");
    return -1;
  }



  struct sockaddr_in connection_address = {0};
  socklen_t addrlen = sizeof(connection_address);
  int newClientFd;
  pid_t parentPid = getpid();

  while (1) {
    if (WEXITSTATUS(cVal) == 5){
      shutdown(sockfd, 2);
      // kill all children
      kill(-(parentPid), SIGTERM); 
      return 0;

    }
      // wait for a new connection on the server socket and accept it
    newClientFd = accept(sockfd, (struct sockaddr *)&connection_address, &addrlen);
    if (newClientFd < 0) {
      perror("Connection Acception Failure\n");
      return -1;
    }
    
  // create pid for fork
   pid_t pid;
   pid = fork();

    // Child process
    if (pid == 0){
       
      

      while(1){
        
        // set bytes of message received from server to 0
        memset(msg, 0, sizeof(msg));
        ssize_t byte_count = recv(newClientFd, msg, BUFSIZE, 0);
        // check if recv worked
        if (byte_count <= 0) {
          break;
        } 
        // struct is received from client as char* so cast it back to struct message_t so that we can
        // separate the command from arguments
        received = (message_t*) msg;
        //print user input
        printf("Client: %s %s\n", received->cmd, received->args);
        int commandReturn = TCP_Func_Exec(newClientFd, received);
        //check if user asked for shutdown
        if (commandReturn == 5){
          send(newClientFd, "Goodbye!", (strlen("Goodbye!")) + 1, 0);
          shutdown(newClientFd, 2);
          return commandReturn;
        }
      }
      // check if fork did not work correctly
    } else if (pid < 0) {
        return -1;
    }
   else {
      // retrieve return value from child
      int wPid = (waitpid(-1, &cVal, WNOHANG));
        if (wPid == -1){
          return -1;
        }
   }
  
  }
  return 0;
}
