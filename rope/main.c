#include "client_handler.h"
#include <string.h>
#include "server_handler.h"

static int _handleClient(char **argv, FILE *command_file) {
    ConnectionHandler connection_handler;
    char *ip = argv[2];
    char *port = argv[3];
    if (createClientConnectionHandler(&connection_handler, ip, port) == ERROR) {
        return ERROR;
    }
    ClientHandler client_handler;
    runClientHandler(&client_handler, &connection_handler, command_file);
    destroyConnectionHandler(&connection_handler);
    return SUCCESS;
}

static int _handleServer(char **argv) {
    ConnectionHandler connection_handler;
    char *port = argv[2];
    if (createServerConnectionHandler(&connection_handler, port) == ERROR) {
        return ERROR;
    }
    ServerHandler server_handler;
    Rope rope;
    createEmptyRope(&rope);
    runServerHandler(&server_handler, &connection_handler, &rope);
    destroyRope(&rope);
    destroyConnectionHandler(&connection_handler);
    return SUCCESS;
}

int main(int argc, char **argv) {
    int number_of_arguments = argc - 1;
    if (number_of_arguments < 2) {
        return ERROR;
    }

    if (strcmp(argv[1], "client") == 0) { // client 127.0.0.1 9898 input.txt
        if (number_of_arguments < 3) {
            return ERROR;
        }
        FILE *command_file = NULL;
        if (number_of_arguments > 3) {
            command_file = fopen(argv[4], "r");
        }
        int exit_code = _handleClient(argv, command_file);
        if (command_file) {
            fclose(command_file);
        }
        return exit_code;

    } else if (strcmp(argv[1], "server") == 0) { // server 9898
        return _handleServer(argv);
    }

    return ERROR;
}
