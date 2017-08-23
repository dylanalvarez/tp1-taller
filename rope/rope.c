#include "rope.h"

void create_rope(rope_t *self) {
    self->root = malloc(sizeof(rope_node_t));
    create_rope_node(self->root, NULL);
}

void concat_ropes(rope_t *left, rope_t *right, rope_t *new_rope) {
    create_rope(new_rope);
    new_rope->root->left = left->root;
    new_rope->root->right = right->root;
    destroy_rope(left);
    destroy_rope(right);
}

void destroy_rope(rope_t *self) {
    destroy_rope_node(self->root);
}
