#include "rope.h"

void create_rope(rope_t *self) {
    self->root = malloc(sizeof(rope_node_t));
    create_rope_node(self->root, NULL);
}

rope_t *concat_ropes(rope_t *left, rope_t *right) {

}

void destroy_rope(rope_t *self) {
    destroy_rope_node(self->root);
}
