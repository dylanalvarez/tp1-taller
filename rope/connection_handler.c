#include <stdio.h>
#include "connection_handler.h"

void createConnectionHandler(ConnectionHandler *self, char *ip, char *port) {
    self->ip = ip;
    self->port = port;
    printf("\nCreated connection in ip %s and port %s\n", ip, port);
}

void sendInteger(ConnectionHandler *self, int content, int size_in_bytes){
    printf("\nSent an integer: %d", content);
}

void sendString(ConnectionHandler *self, char *content, int size_in_bytes){
    printf("\nSent a string: %s", content);
}

int receiveInteger(ConnectionHandler* self, int size_in_bytes){
    printf("\nReceiving an integer");
    return 0;
}

void receiveString(ConnectionHandler* self, char*buffer, int size_in_bytes){
    buffer[0] = 0;
    printf("\nReceiving a string to print");
}


void destroyConnectionHandler(ConnectionHandler *self) {
    printf("\nDestroyed connection in ip %s and port %s\n",
           self->ip,
           self->port
    );
}
