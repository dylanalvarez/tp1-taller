#include <stdbool.h>
#include "node.h"

void createRopeNode(RopeNode *self, const char *string) {
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

void destroyRopeNode(RopeNode *self) {
    free(self->content);
}

bool isLeaf(RopeNode *self) {
    return !(self->left || self->right);
}
