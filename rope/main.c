#include<stdio.h>
#include <stdbool.h>
#include "rope.h"

// GENERIC FUNCTIONS

void assert(bool condition) {
    condition ? printf("OK\n") : printf("FAILED!\n");
}

// ROPE TESTS


// NODE TESTS

void test_new_rope_node_has_weight_of_string() {
    rope_node_t rope_node;
    create_rope_node(&rope_node, "Hola");

    assert(rope_node.weight == 4);

    destroy_rope_node(&rope_node);
}

void test_new_rope_is_leaf() {
    rope_node_t rope_node;
    create_rope_node(&rope_node, "Hola");

    assert(is_leaf(&rope_node));

    destroy_rope_node(&rope_node);
}

// MAIN

int main(int argc, char **argv) {
    test_new_rope_node_has_weight_of_string();
    test_new_rope_is_leaf();
    return 0;
}
