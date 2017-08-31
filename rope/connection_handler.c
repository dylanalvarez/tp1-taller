#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <stdbool.h>

#include "connection_handler.h"

#include <unistd.h>

#define SUCCESS 0
#define ERROR -1

int createConnectionHandler(ConnectionHandler *self, char *ip, char *port,
                            bool is_server) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (is_server) {
        hints.ai_flags = AI_PASSIVE;
    } else {
        hints.ai_flags = 0;
    }

    struct addrinfo *result;
    int exit_code = getaddrinfo(ip, port, &hints, &result);
    if (exit_code != SUCCESS) {
        fprintf(stderr, "%s\n", gai_strerror(exit_code));
        return ERROR;
    }

    bool success = false;
    int skt = 0;
    for (struct addrinfo *ptr = result;
         ptr != NULL && !success; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != SUCCESS) {
            return ERROR;
        } else {
            exit_code = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (exit_code != SUCCESS) {
                close(skt);
            } else {
                success = true;
            }
        }
    }

    freeaddrinfo(result);

    if (!success) {
        return ERROR;
    }

    self->skt = skt;
    return SUCCESS;
}

void sendInteger(ConnectionHandler *self, int content, int size_in_bytes) {
    printf("\nSent an integer: %d", content);
}

void sendString(ConnectionHandler *self, char *content, int size_in_bytes) {
    printf("\nSent a string: %s", content);
}

int receiveInteger(ConnectionHandler *self, int size_in_bytes) {
    printf("\nReceiving an integer");
    return 0;
}

void receiveString(ConnectionHandler *self, char *buffer, int size_in_bytes) {
    buffer[0] = 0;
    printf("\nReceiving a string to print");
}


void destroyConnectionHandler(ConnectionHandler *self) {
    printf("\nDestroyed connection in ip %s and port %s\n",
           self->ip,
           self->port
    );
}
