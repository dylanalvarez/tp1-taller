#ifndef TP1_TALLER_ROPE_H
#define TP1_TALLER_ROPE_H

#include "node.h"

typedef struct {
    rope_node_t *root;
} rope_t;

void create_rope(rope_t *self);

rope_t *concat_ropes(rope_t *left, rope_t *right);

void destroy_rope(rope_t *self);

#endif //TP1_TALLER_ROPE_H
