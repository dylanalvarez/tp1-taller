#include <stdio.h>
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

void split_ropes(rope_t *source, int index, rope_t *left, rope_t *right) {

}

int get_rope_content_length(rope_t *self) {
    int total = 0;
    rope_node_t *node = self->root;
    while (node) {
        total += node->weight;
        node = node->right;
    }
    return total;
}

void fill_buffer(rope_node_t *node, char *buffer, int *position) {
    if (!node) { return; }
    fill_buffer(node->left, buffer, position);

    if (node->content) {
        size_t length = strlen(node->content);
        for (int i = *position; i < length + *position; i++) {
            buffer[i] = node->content[i - *position];
        }
        *position += length;
        buffer[*position] = (char) 0;
    }

    fill_buffer(node->right, buffer, position);
}

void get_rope_content(rope_t *self, char *buffer) {
    int position = 0;
    buffer[0] = (char) 0;
    fill_buffer(self->root, buffer, &position);
}

void destroy_rope(rope_t *self) {
    destroy_rope_node(self->root);
}
