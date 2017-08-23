#include <stdbool.h>
#include "node.h"

void create_rope_node(rope_node_t *self, const char *string) {
    self->left = NULL;
    self->right = NULL;
    if (string == NULL) {
        self->content = NULL;
    } else {
        size_t string_length = strlen(string);
        self->weight = string_length;
        size_t string_size = string_length + 1;
        self->content = malloc(string_size);
        strncpy(self->content, string, string_size);
    }
}

void destroy_rope_node(rope_node_t *self) {
    free(self->content);
}

bool is_leaf(rope_node_t *self) {
    return !(self->left || self->right);
}
