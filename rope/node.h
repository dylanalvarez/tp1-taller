#ifndef TP1_TALLER_NODE_H
#define TP1_TALLER_NODE_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct rope_node {
    char *content;
    size_t weight;
    struct rope_node *left;
    struct rope_node *right;
} rope_node_t;

void create_rope_node(rope_node_t *self, const char *string);

bool is_leaf(rope_node_t *self);

void destroy_rope_node(rope_node_t *self);

#endif //TP1_TALLER_NODE_H
