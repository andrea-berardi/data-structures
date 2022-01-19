#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/data_structures/b_trees.h"

void DiskWrite(BTNode *node) {
    return;
}
BTNode *DiskRead(BTNode *xci /* x.children[i] */) {
    return xci;
}

BTNode *BTNewNode(size_t t, bool leaf) {
    BTNode *x = malloc(sizeof(BTNode));

    x->t = t; // number of keys (NOT the cardinality) - capacity
    x->n = 0; // number of keys - cardinality
    x->leaf = leaf; // will be determined by the function call, if provided
    x->keys = malloc(sizeof(int) * 2 * t - 1); // array of keys of the node
    x->children = malloc(sizeof(BTNode *) * (2 * t)); // array of children of the node

    return x;
}

BTTree *BTNewTree(size_t t) {
    BTTree *tree = malloc(sizeof(BTTree));

    tree->t = t; // starting capacity

    tree->root = BTNewNode(t, true);
    tree->root->t = t; // root capacity
    tree->root->n = 0; // root cardinality
    tree->root->leaf = true; // root is a leaf
    tree->root->parent = NULL; // root has no parent
    tree->root->children = NULL; // root has no children (yet!)

    DiskWrite(tree->root);

    return tree;
}

void BTSplitChild(BTNode *x, size_t i) {
    size_t t = x->t;

    BTNode *z = BTNewNode(t, x->leaf);
    BTNode *y = x->children[i];

    z->leaf = y->leaf;
    z->n = t - 1;

    for (size_t j = 0; j < t - 1; ++j) {
        z->keys[j] = y->keys[j + t];
    }

    if (y->leaf == false) {
        for (size_t j = 0; j < t; ++j) {
            z->children[j] = y->children[j + t];
        }
    }

    y->n = t - 1;

    for (size_t j = x->n; j >= i + 1; --j) {
        x->children[j + 1] = x->children[j];
    }

    x->keys[i] = y->keys[t - 1];
    x->n += 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);
}

void BTInsertNonFull(BTNode *x, int k) {
    ssize_t i = x->n - 1;

    if (x->leaf == true) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i -= 1;
        }

        x->keys[i + 1] = k;
        x->n += 1;

        DiskWrite(x);
    } else {
        while (i >= 0 && k < x->keys[i]) i -= 1;
        i += 1;

        DiskRead(x->children[i]);

        if (x->children[i]->n == 2 * x->t - 1) {
            BTSplitChild(x, i);

            if (k > x->keys[i]) i += 1;
        }

        BTInsertNonFull(x->children[i], k);
    }
}

void BTInsert(BTTree *T, int k) {
    size_t t = T->t; // number of keys (NOT the cardinality) - capacity

    BTNode *r = T->root;

    if (r->n == 2 * t - 1) {
        BTNode *s = BTNewNode(t, false);
        T->root = s;
        s->leaf = false;
        s->n = 0;
        s->children[0] = r;

        BTSplitChild(s, 0);

        size_t i = s->keys[0] < k ? 1 : 0;
        BTInsertNonFull(s->children[i], k);
    } else {
        BTInsertNonFull(r, k);
    }
}

NodeAndIndex BTSearch(BTNode *x, int k) {
    size_t i = 1;

    while (i <= x->n && k > x->keys[i]) i += 1;

    if (i <= x->n && k == x->keys[i]) {
        NodeAndIndex nx;

        nx.node = x;
        nx.index = i;

        return nx;
    } else if (x->leaf == true) {
        NodeAndIndex nx;

        nx.node = NULL;
        nx.index = i;

        return nx;
    } else {
        DiskRead(x->children[i]);

        return BTSearch(x->children[i], k);
    }
}

void BTDeleteKey(BTNode *x, int k) {
    // TODO: implement
}
