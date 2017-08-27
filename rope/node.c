#include <string.h>
#include "node.h"

void createEmptyRopeNode(RopeNode *self) {
    self->left = NULL;
    self->right = NULL;
    self->weight = 0;
    self->content = NULL;
}

static void
_setRopeNodeContent(RopeNode *self, const char *string,
                    size_t initial_position, size_t character_count) {
    self->weight = character_count;
    self->content = malloc(character_count + 1);
    memcpy(self->content, string + initial_position, character_count);
    self->content[character_count] = 0;
}

void createRopeNode(RopeNode *self, const char *string) {
    createEmptyRopeNode(self);
    if (string) {
        _setRopeNodeContent(self, string, 0, strlen(string));
    }
}

bool isLeaf(RopeNode *self) {
    return !(self->left || self->right);
}

size_t getSubRopeContentLength(RopeNode *self) {
    size_t total = 0;
    while (self) {
        total += self->weight;
        self = self->right;
    }
    return total;
}

void _removeContent(RopeNode *self) {
    free(self->content);
    self->content = NULL;
}

void
splitRopeNode(RopeNode *self, size_t index, RopeNode *left, RopeNode *right) {
    createEmptyRopeNode(left);
    _setRopeNodeContent(left, self->content, 0, index);

    createEmptyRopeNode(right);
    _setRopeNodeContent(right, self->content, index,
                        strlen(self->content) - index);

    appendLeftChild(self, left);
    appendRightChild(self, right);

    _removeContent(self);
}

void appendLeftChild(RopeNode *self, RopeNode *left_child) {
    self->left = left_child;
    self->weight = getSubRopeContentLength(self->left);
}

void appendRightChild(RopeNode *self, RopeNode *right_child) {
    self->right = right_child;
}

void destroyRopeNode(RopeNode *self) {
    if (self->content) { _removeContent(self); }
}
