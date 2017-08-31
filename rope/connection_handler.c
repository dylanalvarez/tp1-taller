#include <stdio.h>
#include "connection_handler.h"

void createConnectionHandler(ConnectionHandler *self, char *ip, char *port) {
    self->ip = ip;
    self->port = port;
    printf("\nCreated connection in ip %s and port %s\n", ip, port);
}

void destroyConnectionHandler(ConnectionHandler *self) {
    printf("\nDestroyed connection in ip %s and port %s\n",
           self->ip,
           self->port
    );
}
