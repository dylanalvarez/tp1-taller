#include <string.h>
#include "node.h"

static void _createEmptyRopeNode(RopeNode *self) {
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
    memcpy(self->content, string + initial_position, character_count); // NOLINT
    self->content[character_count] = 0;
}

void createRopeNode(RopeNode *self, const char *string) {
    _createEmptyRopeNode(self);
    if (string) {
        _setRopeNodeContent(self, string, 0, strlen(string));
    }
}

bool isLeaf(RopeNode *self) {
    return !(self->left || self->right);
}

size_t getContentLengthFromRoot(RopeNode *self) {
    size_t total = 0;
    while (self) {
        total += self->weight;
        self = self->right;
    }
    return total;
}

void
splitRopeNode(RopeNode *source, size_t index, RopeNode *left, RopeNode *right) {
    _createEmptyRopeNode(left);
    _setRopeNodeContent(left, source->content, 0, index);

    _createEmptyRopeNode(right);
    _setRopeNodeContent(right, source->content, index,
                        strlen(source->content) - index);

    source->left = left;
    source->right = right;
    source->weight = left->weight;
    free(source->content);
    source->content = NULL;
}

void destroyRopeNode(RopeNode *self) {
    if (self->content) { free(self->content); }
}
