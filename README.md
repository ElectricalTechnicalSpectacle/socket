socket
======

This is an example of socket communication between python program (server) and C program (client)

Issue make for the C program. and run the python program as executable.

Python (server)
```sh
./server
```

C (client)
```sh
make
./client
```


To compile client on beaglebone from existing object file, run:

gcc -std=c99 -g -Wall -lpthread -pthread -o client client.o
