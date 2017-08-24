#ifndef TP1_TALLER_ROPE_H
#define TP1_TALLER_ROPE_H

#include "node.h"

typedef struct {
    rope_node_t *root;
} rope_t;

// Post: self is a rope containing an empty string.
void create_rope(rope_t *self);

// Pre:  left and right are both created ropes.
// Post: left and right are both destroyed,
//       destination is created with their contents.
void concat_ropes(
        rope_t *left_source,
        rope_t *right_source,
        rope_t *destination
);

// Pre:  source is a created rope, left_length is a number between 0 and
//       get_rope_content_length(&source)
// Post: source is destroyed, left and right are created, the first n characters
//       being n = left_length go to left and the rest, to right.
void split_ropes(
        rope_t *source, int left_length,
        rope_t *left_destination,
        rope_t *right_destination
);

// Faster way of getting the length of the string contained within self
int get_rope_content_length(rope_t *self);

// Pre:  buffer's length is at least get_rope_content_length(&self) + 1 bytes
// Post: buffer contains the string contained within self
void get_rope_content(rope_t *self, char *buffer);

void destroy_rope(rope_t *self);

#endif //TP1_TALLER_ROPE_H
