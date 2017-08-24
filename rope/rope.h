#ifndef TP1_TALLER_ROPE_H
#define TP1_TALLER_ROPE_H

#include "node.h"

typedef struct {
    RopeNode *root;
} Rope;

// Post: self is a rope containing an empty string.
void createRope(Rope *self);

// Pre:  left and right are both created ropes.
// Post: left and right are both destroyed,
//       destination is created with their contents.
void concatRopes(
        Rope *left_source,
        Rope *right_source,
        Rope *destination
);

// Pre:  source is a created rope, left_length is a number between 0 and
//       getRopeContentLength(&source)
// Post: source is destroyed, left and right are created, the first n characters
//       being n = left_length go to left and the rest, to right.
void splitRopes(
        Rope *source, int left_length,
        Rope *left_destination,
        Rope *right_destination
);

// Faster way of getting the length of the string contained within self
int getRopeContentLength(Rope *self);

// Pre:  buffer's length is at least getRopeContentLength(&self) + 1 bytes
// Post: buffer contains the string contained within self
void getRopeContent(Rope *self, char *buffer);

void destroyRope(Rope *self);

#endif //TP1_TALLER_ROPE_H
