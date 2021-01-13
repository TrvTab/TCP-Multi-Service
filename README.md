# TCP-Multi-Service

This program creates TCP server that is able to serve the requests of multiple clients simultaneously through the use of multi-processing in C. The client has access to multiple mathematical operations as well as sports statistics and the weather at a North American postal code. The statistics and weather retrieval is done in Python through HTML scraping and API calls respectively.


Compiled using Makefile with the command "make".

After compilation, the server can be run by executing

./server {address} {post}

in the command line


Clients can then be run with

./client {address} {post}

in the command line



### Possible client requests: 
  
  add {x} {y}  which executes x + y

  multiply {x} {y} which executes x * y

  divide {x} {y} which executes  x / y

  factorial {x} which executes x!

  fibonacci {x} which executes the fibonacci number of x

  logarithm {x} {y} which executes the log of x with a base of y

  stats NHL {Points | Goals | Plus/Minus | GAA | SavePercentage | Wins}

  weather {postal code}





