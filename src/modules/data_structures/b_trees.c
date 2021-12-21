#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/data_structures/b_trees.h"

void DiskRead(BTNode x[]) {
    // TODO
}
void DiskWrite(BTNode *x) {
    // TODO
}

typedef struct node_and_index {
    bool is_null; // `true` when NULL, `false` when not NULL
    BTNode *node;
    size_t index;
} NodeAndIndex;

NodeAndIndex BTSearch(BTNode *x, int k) {
    size_t i = 1;

    while (i <= x->n && k > x->keys[i]) {
        i += 1;
    }

    if (i <= x->n && k == x->keys[i]) {
        NodeAndIndex nx;
        nx.is_null = false;
        nx.node = x;
        nx.index = i;

        return nx;
    } else if (x->leaf == true) {
        NodeAndIndex nx;
        nx.is_null = true;
        nx.node = NULL;
        nx.index = i;

        return nx;
    } else {
        DiskRead(x->children[i]);
        return BTSearch(x->children[i], k);
    }
}
