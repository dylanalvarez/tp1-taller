#ifndef TP1_TALLER_CONNECTION_HANDLER_H
#define TP1_TALLER_CONNECTION_HANDLER_H

#include <netdb.h>
#include <stdio.h>
#include "connection_handler.h"

typedef struct {
    char *ip;
    char *port;
} ConnectionHandler;


void createConnectionHandler(ConnectionHandler *self, char *ip, char *port);

void destroyConnectionHandler(ConnectionHandler *self);

#endif //TP1_TALLER_CONNECTION_HANDLER_H
