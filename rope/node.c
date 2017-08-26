#include <stdbool.h>
#include "node.h"

void createRopeNode(RopeNode *self, const char *string) {
    self->left = NULL;
    self->right = NULL;
    if (string == NULL) {
        self->content = NULL;
        self->weight = 0;
    } else {
        size_t string_length = strlen(string);
        self->weight = string_length;
        size_t string_size = string_length + 1;
        self->content = malloc(string_size);
        strncpy(self->content, string, string_size);
    }
}

bool isLeaf(RopeNode *self) {
    return !(self->left || self->right);
}

void
splitRopeNode(RopeNode *source, size_t index, RopeNode *left, RopeNode *right) {
    size_t string_length = strlen(source->content);
    char left_string[index + 1];
    memcpy(left_string, source->content, index);
    left_string[index] = 0;
    char right_string[string_length - index + 1];
    memcpy(right_string, source->content + index, string_length - index);
    right_string[string_length - index] = 0;
    createRopeNode(left, left_string);
    createRopeNode(right, right_string);
    source->left = left;
    source->right = right;
    source->weight = left->weight;
    free(source->content);
    source->content = NULL;
}

void destroyRopeNode(RopeNode *self) {
    if (self->content) {
        free(self->content);
    }
}

