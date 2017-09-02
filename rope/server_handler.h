#ifndef TP1_TALLER_SERVER_HANDLER_H
#define TP1_TALLER_SERVER_HANDLER_H


#include "connection_handler.h"
#include "rope.h"

typedef struct {
    ConnectionHandler *connection_handler;
    Rope *rope;
} ServerHandler;

// Pre:  connection_handler was created, server_handler is not NULL.
// Post: connection_handler will be called to receive instructions
//       from a client until it disconnects

void runServerHandler(ServerHandler *server_handler,
                      ConnectionHandler *connection_handler,
                      Rope *rope);

#endif //TP1_TALLER_SERVER_HANDLER_H
