#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/data_structures/b_trees.h"

BTNode *DiskWrite(BTNode *node) {
    return node;
}

BTNode *DiskRead(BTNode *xci) {
    return xci;
}

BTNode *BTNewNode(ssize_t t, bool leaf) {
    BTNode *x = malloc(sizeof(BTNode));

    x->t = t; // number of keys (NOT the cardinality) - capacity
    x->n = 0; // number of keys - cardinality
    x->leaf = leaf; // will be determined by the function call, if provided
    x->keys = malloc(sizeof(int) * 2 * t - 1); // array of keys of the node
    x->children = malloc(sizeof(BTNode *) * (2 * t)); // array of children of the node

    return x;
}

BTTree *BTNewTree(ssize_t t) {
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

void BTSplitChild(BTNode *x, ssize_t i) {
    ssize_t t = x->t;

    BTNode *z = BTNewNode(t, x->leaf);
    BTNode *y = x->children[i];

    z->leaf = y->leaf;
    z->n = t - 1;

    for (ssize_t j = 0; j < t - 1; ++j) {
        z->keys[j] = y->keys[j + t];
    }

    if (y->leaf == false) {
        for (ssize_t j = 0; j < t; ++j) {
            z->children[j] = y->children[j + t];
        }
    }

    y->n = t - 1;

    for (ssize_t j = x->n; j >= i + 1; --j) {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z;

    for (ssize_t j = x->n - 1; j >= i; --j) {
        printf("j = %zu\n", j);
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[t - 1];
    x->n += 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);
}

void BTInsertNonFull(BTNode *x, int k) {
    printf("x-n: %zu\n", x->n);
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
            BTSplitChild(x->children[i], i);

            if (k > x->keys[i]) i += 1;
        }

        BTInsertNonFull(x->children[i], k);
    }
}

void BTInsert(BTTree *T, int k) {
    ssize_t t = T->t; // number of keys (NOT the cardinality) - capacity

    BTNode *r = T->root;

    if (r->n == 2 * t - 1) {
        BTNode *s = BTNewNode(t, false);
        T->root = s;
        s->leaf = false;
        s->n = 0;
        s->children[0] = r;

        BTSplitChild(s, 0);

        BTInsertNonFull(s, k);
    } else {
        BTInsertNonFull(r, k);
    }
}

NodeAndIndex BTSearch(BTNode *x, int k) {
    ssize_t i = 1;

    while (i <= x->n && k > x->keys[i]) i += 1;

    if (i <= x->n && k == x->keys[i]) {
        NodeAndIndex nx = {
                .node = x,
                .index = i
        };

        return nx;
    } else if (x->leaf == true) {
        NodeAndIndex nx = {
                .node = NULL,
                nx.index = i
        };

        return nx;
    } else {
        DiskRead(x->children[i]);

        return BTSearch(x->children[i], k);
    }
}

int BTMin(BTNode *x) {
    if (x == NULL) {
        return -1;
    } else if (x->leaf == true) {
        return x->keys[0];
    } else {
        DiskRead(x->children[0]);

        return BTMin(x->children[0]);
    }
}

int BTMax(BTNode *x) {
    if (x == NULL) {
        return -1;
    } else if (x->leaf == true) {
        return x->keys[x->n];
    } else {
        DiskRead(x->children[x->n]);

        return BTMin(x->children[x->n]);
    }
}

int BTPredecessor(ssize_t k, BTNode *x) {
    if (x->leaf == false) {
        DiskRead(x->children[k]);

        return BTMax(x);
    } else if (k > 0) {
        return x->keys[k - 1];
    } else {
        BTNode *z = x;

        while (true) {
            if (z->parent == NULL) {
                return -1;
            }

            BTNode *y = z->parent;
            int j = 0;

            DiskRead(y->children[0]);

            while (y->children[j] != x) {
                j += 1;
                DiskRead(y->children[j]);
            }

            if (j == 0) {
                z = y;
            } else {
                return y->keys[j - 1];
            }
        }
    }
}

void BTDeleteLeaf(BTNode *x, int k) { // can be optimized by using the `i` from the search
    ssize_t i = 0;

    while (i < x->n && k > x->keys[i]) i += 1;

    if (i < x->n && k == x->keys[i]) {
        for (ssize_t j = i; j < x->n - 1; ++j) {
            x->keys[j] = x->keys[j + 1];
        }

        x->n -= 1;
    }

    DiskWrite(x);

    // test
    if (x->n == 0) {
        BTNode *y = x->parent;
        int j = 0;

        while (y->children[j] != x) {
            j += 1;
        }

        y->children[j] = NULL;
        y->n -= 1;

        DiskWrite(y);
    }
}

void BTDeleteNonLeaf(BTNode *x, int k) {
    ssize_t i = 0;

    while (i < x->n && k > x->keys[i]) i += 1;

    if (i < x->n && k == x->keys[i]) {
        BTNode *y = x->children[i];
        BTNode *z = x->children[i + 1];

        if (y->n >= x->t) {
            int pred = BTPredecessor(i, x);
            x->keys[i] = pred;
            BTDeleteNonLeaf(y, pred);
        } else if (z->n >= x->t) {
            int successor = BTMax(z);
            x->keys[i] = successor;
            BTDeleteNonLeaf(z, successor);
        } else {
            x->keys[i] = y->keys[y->n - 1];
            y->n -= 1;
            z->n -= 1;

            DiskWrite(y);
            DiskWrite(z);
        }
    } else {
        BTNode *y = x->children[i];
        BTNode *z = x->children[i + 1];

        if (y->n >= x->t) {
            int pred = BTPredecessor(i, x);
            x->keys[i] = pred;
            BTDeleteNonLeaf(y, pred);
        } else if (z->n >= x->t) {
            int successor = BTMax(z);
            x->keys[i] = successor;
            BTDeleteNonLeaf(z, successor);
        } else {
            x->keys[i] = y->keys[y->n - 1];
            y->n -= 1;
            z->n -= 1;

            DiskWrite(y);
            DiskWrite(z);
        }
    }

    // test
    if (x->n == 0) {
        BTNode *y = x->parent;
        int j = 0;

        while (y->children[j] != x) {
            j += 1;
        }

        y->children[j] = NULL;
        y->n -= 1;

        DiskWrite(y);
    }
}

void BTDelete(BTTree *T, int k) {
    NodeAndIndex nx = BTSearch(T->root, k);

    if (nx.node == NULL) {
        return;
    }

    if (nx.node->leaf == true) {
        BTDeleteLeaf(nx.node, k);
    } else {
        BTDeleteNonLeaf(nx.node, k);
    }
}
