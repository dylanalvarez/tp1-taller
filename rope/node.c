#include <string.h>
#include "node.h"

static void _createEmptyRopeNode(RopeNode *self) {
    self->left = NULL;
    self->right = NULL;
    self->weight = 0;
    self->content = NULL;
}

static void _setRopeNodeContent(RopeNode *self, const char *string) {
    size_t string_length = strlen(string);
    self->weight = string_length;
    self->content = malloc(string_length + 1);
    strncpy(self->content, string, string_length + 1); // NOLINT

}

void createRopeNode(RopeNode *self, const char *string) {
    _createEmptyRopeNode(self);
    if (string) {
        _setRopeNodeContent(self, string);
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

