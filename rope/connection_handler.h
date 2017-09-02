#ifndef TP1_TALLER_CONNECTION_HANDLER_H
#define TP1_TALLER_CONNECTION_HANDLER_H

#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "connection_handler.h"

typedef struct {
    int skt;
    int peer_skt;
} ConnectionHandler;

// Post: returns ERROR on failure
int
createClientConnectionHandler(ConnectionHandler *self, char *ip, char *port);

// Post: returns ERROR on failure
int createServerConnectionHandler(ConnectionHandler *self, char *port);

void sendInteger(ConnectionHandler *self, int content, bool short_int);

void sendString(ConnectionHandler *self, char *content, int size_in_bytes);

// Post: returns ERROR on failure
int receiveInteger(ConnectionHandler *self, int *buffer, bool short_int);

// Post: returns ERROR on failure
int receiveString(ConnectionHandler *self, char *buffer, int size_in_bytes);

void destroyConnectionHandler(ConnectionHandler *self);

#endif //TP1_TALLER_CONNECTION_HANDLER_H
