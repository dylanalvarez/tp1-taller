#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>


#if !defined MSG_NOSIGNAL
# define MSG_NOSIGNAL 0 // for macOS compatibility
#endif

#include "connection_handler.h"
#include "constants.h"


int _createConnectionHandler(ConnectionHandler *self, char *ip, char *port) {
    bool is_server = !ip;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (is_server) {
        hints.ai_flags = AI_PASSIVE;
    } else {
        hints.ai_flags = 0;
    }

    self->skt = -1;
    self->peer_skt = -1;

    struct addrinfo *result;
    int exit_code = getaddrinfo(ip, port, &hints, &result);
    if (exit_code != SUCCESS) {
        fprintf(stderr, "%s\n", gai_strerror(exit_code));
        return ERROR;
    }

    bool success = false;
    int skt = -1;

    for (struct addrinfo *ptr = result;
         ptr != NULL && !success; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1 && !is_server) {
            exit_code = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (exit_code != -1) {
                success = true;
            } else {
                close(skt);
            }
        }
    }

    if (is_server) {
        self->skt = skt;
        success = false;
        if (bind(skt, result->ai_addr, result->ai_addrlen) != -1
            && listen(skt, 1) != -1) {
            int client_skt = accept(skt, NULL, NULL);
            if (client_skt != -1) {
                success = true;
                self->peer_skt = client_skt;
            }
        }
        if (!success) {
            close(skt);
        }
    } else {
        self->peer_skt = skt;
    }

    freeaddrinfo(result);

    if (!success) {
        return ERROR;
    }

    return SUCCESS;
}

int
createClientConnectionHandler(ConnectionHandler *self, char *ip, char *port) {
    return _createConnectionHandler(self, ip, port);
}

int createServerConnectionHandler(ConnectionHandler *self, char *port) {
    return _createConnectionHandler(self, NULL, port);
}

void sendInteger(ConnectionHandler *self, int content, bool short_int) {
    int size_in_bytes = short_int ? 2 : 4;
    int big_endian_content = short_int ? htons(content) : htonl(content);
    char *data = (char *) &big_endian_content;
    sendString(self, data, size_in_bytes);
}

void sendString(ConnectionHandler *self, char *content, int size_in_bytes) {
    int sent_bytes = 0;
    bool error = false;

    while (sent_bytes < size_in_bytes && !error) {
        int sent = (int) send(self->peer_skt, &content[sent_bytes],
                              (size_t) (size_in_bytes - sent_bytes),
                              MSG_NOSIGNAL);
        if (sent <= 0) {
            printf("Error: %s\n", strerror(errno));
            error = true;
        } else {
            sent_bytes += sent;
        }
    }
}

int _receiveString(ConnectionHandler *self, char *buffer, int size_in_bytes) {
    int received_bytes = 0;
    bool error = false;
    while (received_bytes < size_in_bytes && !error) {
        int received = (int) recv(self->peer_skt,
                                  &buffer[received_bytes],
                                  (size_t) (size_in_bytes -
                                            received_bytes),
                                  MSG_NOSIGNAL);
        if (received <= 0) {
            error = true;
        } else {
            received_bytes += received;
        }
    }

    return error ? ERROR : SUCCESS;
}


int
receiveString(ConnectionHandler *self, char *buffer, int size_in_bytes) {
    int exit_code = _receiveString(self, buffer, size_in_bytes);

    buffer[size_in_bytes] = 0;

    return exit_code;
}


int
receiveInteger(ConnectionHandler *self, int *content, bool short_int) {
    int size_in_bytes = short_int ? 2 : 4;
    char *buffer = (char *) content;
    int exit_code = _receiveString(self, buffer, size_in_bytes);
    if (exit_code != SUCCESS) {
        return exit_code;
    }
    if (short_int) {
        buffer[3] = buffer[1];
        buffer[2] = buffer[0];
        buffer[1] = 0;
        buffer[0] = 0;
    }
    int asd = *(int *) buffer;
    *(int *) buffer = ntohl(asd);
    return exit_code;
}


void destroyConnectionHandler(ConnectionHandler *self) {
    if (self->peer_skt != -1) {
        shutdown(self->peer_skt, SHUT_RDWR);
        close(self->peer_skt);
    }
    if (self->skt != -1) {
        shutdown(self->skt, SHUT_RDWR);
        close(self->skt);
    }
}
