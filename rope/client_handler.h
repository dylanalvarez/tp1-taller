#ifndef TP1_TALLER_COMMAND_H
#define TP1_TALLER_COMMAND_H

#include "connection_handler.h"
#include "constants.h"


typedef struct {
    ConnectionHandler *connection_handler;
    char input[MAX_INPUT_LENGTH];
    FILE *command_file;
} ClientHandler;


// Pre:  connection_handler was created, client_handler is not NULL.
// Post: connection_handler will be called to send instructions
//       received from a file to the server,
//       or stdin if command_file is NULL, until end of file (ctrl + D).
void runClientHandler(ClientHandler *client_handler,
                      ConnectionHandler *connection_handler,
                      FILE *command_file);

#endif //TP1_TALLER_COMMAND_H
