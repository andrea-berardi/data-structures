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
    tree->root->n = 0; // root cardinality
    tree->root->leaf = true; // root is a leaf
    tree->root->parent = NULL; // root has no parent
    tree->root->children = NULL; // root has no children (yet!)

    DiskWrite(tree->root);

    return tree;
}

void BTSplitChild(BTTree *T, BTNode *x, ssize_t i) {
    BTNode *z = BTNewNode(T->t, x->leaf);
    BTNode *y = x->children[i];

    z->leaf = y->leaf;
    z->n = T->t - 1;

    for (ssize_t j = 0; j < T->t - 1; ++j) {
        z->keys[j] = y->keys[j + T->t];
    }

    if (y->leaf == false) {
        for (ssize_t j = 0; j < T->t; ++j) {
            z->children[j] = y->children[j + T->t];
        }
    }

    y->n = T->t - 1;

    for (ssize_t j = x->n; j >= i + 1; --j) {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z;

    for (ssize_t j = x->n - 1; j >= i; --j) {
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[T->t - 1];
    x->n += 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);

    // free(z); // remove comment only when actually writing to disk
}

void BTInsertNonFull(BTTree *T, BTNode *x, int k) {
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

        if (x->children[i]->n == 2 * T->t - 1) {
            BTSplitChild(T, x, i);

            if (k > x->keys[i]) i += 1;
        }

        BTInsertNonFull(T, x->children[i], k);
    }
}

void BTInsertKey(BTTree *T, int key) {
    BTNode *r = T->root;

    if (r->n == 2 * T->t - 1) {
        BTNode *s = BTNewNode(T->t, false);
        T->root = s;
        s->leaf = false;
        s->n = 0;
        s->children[0] = r;

        BTSplitChild(T, s, 0);

        BTInsertNonFull(T, s, key);
    } else {
        BTInsertNonFull(T, r, key);
    }
}

NodeAndIndex BTSearchKey(BTNode *x, int k) {
    ssize_t i = 0;

    while (i < x->n && k > x->keys[i]) i += 1;

    if (i < x->n && k == x->keys[i]) {
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

        return BTSearchKey(x->children[i], k);
    }
}

/*void BTMerge(BTTree *T, BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i + 1];

    y->keys[T->t - 1] = x->keys[i];

    for (ssize_t j = 0; j < z->n; ++j) {
        y->keys[j + T->t] = z->keys[j];
    }

    if (y->leaf == false) {
        for (ssize_t j = 0; j < z->n; ++j) {
            y->children[j + T->t] = z->children[j];
        }
    }

    y->n += z->n + 1;

    for (ssize_t j = i; j < x->n - 1; ++j) {
        x->keys[j] = x->keys[j + 1];
    }

    for (ssize_t j = i + 1; j < x->n; ++j) {
        x->children[j] = x->children[j + 1];
    }

    x->n -= 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);

    // free(z); // remove comment only when actually writing to disk
}*/

void BTDeleteFromLeaf(BTNode *x, ssize_t i) {
    for (ssize_t j = i + 1; j < x->n; ++j) {
        x->keys[j - 1] = x->keys[j];
    }

    x->n -= 1;

    DiskWrite(x);
}

ssize_t BTFindKey(BTNode *x, int k) {
    ssize_t i = 0;

    while (i < x->n && k > x->keys[i]) i += 1;

    return i;
}

int BTPredecessor(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];

    while (y->leaf == false) {
        y = y->children[y->n];
    }

    return y->keys[y->n - 1];
}

int BTSuccessor(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i + 1];

    while (y->leaf == false) {
        y = y->children[0];
    }

    return y->keys[0];
}

void BTBorrowFromPrevious(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i - 1];

    for (ssize_t j = y->n - 1; j >= 0; --j) {
        y->keys[j + 1] = y->keys[j];
    }

    if (y->leaf == false) {
        for (ssize_t j = y->n; j >= 0; --j) {
            y->children[j + 1] = y->children[j];
        }
    }

    y->keys[0] = x->keys[i - 1];

    if (y->leaf == false) {
        y->children[0] = z->children[z->n];
    }

    y->keys[i - 1] = z->keys[z->n - 1];

    y->n += 1;
    z->n -= 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);
}

void BTBorrowFromNext(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i + 1];

    y->keys[y->n] = x->keys[i];

    if (y->leaf == false) {
        y->children[y->n + 1] = z->children[0];
    }

    y->keys[i] = z->keys[0];

    for (ssize_t j = 1; j < z->n; ++j) {
        z->keys[j - 1] = z->keys[j];
    }

    if (y->leaf == false) {
        for (ssize_t j = 1; j <= z->n; ++j) {
            z->children[j - 1] = z->children[j];
        }
    }

    y->n += 1;
    z->n -= 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);
}

void BTMerge(BTTree *T, BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i + 1];

    y->keys[T->t - 1] = x->keys[i];

    for (ssize_t j = 0; j < z->n; ++j) {
        y->keys[T->t + 1] = z->keys[j];
    }

    if (y->leaf == false) {
        for (ssize_t j = 0; j <= z->n; ++j) {
            y->children[T->t + 1] = z->children[j];
        }
    }

    for (ssize_t j = i + 1; j < x->n; ++j) {
        x->keys[j - 1] = x->keys[j];
    }

    for (ssize_t j = i + 2; j <= x->n; ++j) {
        x->children[j - 1] = x->children[j];
    }

    y->n += z->n + 1;

    x->n -= 1;

    DiskWrite(x);
    DiskWrite(y);
    DiskWrite(z);

    free(z);
}

void BTFillNode(BTTree *T, BTNode *x, ssize_t i) {
    if (i != 0 && x->children[i - 1]->n >= T->t) {
        BTBorrowFromPrevious(x, i);
    } else if (i != x->n && x->children[i + 1]->n >= T->t) {
        BTBorrowFromNext(x, i);
    } else {
        if (i != x->n) {
            BTMerge(T, x, i);
        } else {
            BTMerge(T, x, i - 1);
        }
    }
}

void BTRemoveFromNode(BTTree *T, BTNode *x, int k);

void BTDeleteFromNonLeaf(BTTree *T, BTNode *x, ssize_t i) {
    int k = x->keys[i];

    if (x->children[i]->n >= T->t) {
        int p = BTPredecessor(x, i);

        x->keys[i] = p;

        BTRemoveFromNode(T, x->children[i], p);
    } else if (x->children[i + 1]->n >= T->t) {
        int s = BTSuccessor(x, i);

        x->keys[i] = s;

        BTRemoveFromNode(T, x->children[i + 1], s);
    } else {
        BTMerge(T, x, i);

        BTRemoveFromNode(T, x->children[i], k);
    }
}

void BTRemoveFromNode(BTTree *T, BTNode *x, int k) {
    ssize_t i = BTFindKey(x, k);

    if (i < x->n && x->keys[i] == k) {
        if (x->leaf == true) {
            BTDeleteFromLeaf(x, i);
        } else {
            BTDeleteFromNonLeaf(T, x, i);
        }
    } else {
        if (x->leaf == true) {
            return; // key not found
        }

        bool flag = (i == x->n) ? true : false;

        if (x->children[i]->n < T->t) {
            BTFillNode(T, x, i);
        }

        if (flag == true && i > x->n) {
            BTRemoveFromNode(T, x->children[i - 1], k);
        } else {
            BTRemoveFromNode(T, x->children[i], k);
        }
    }
}

void BTDeleteKey(BTTree *T, int key) {
    if (T->root == NULL || !T->root) {
        return; // empty tree
    }

    BTRemoveFromNode(T, T->root, key);

    if (T->root->n == 0) {
        BTNode *root = T->root;

        if (T->root->leaf == true) {
            T->root = NULL;
        } else {
            T->root = T->root->children[0];
        }

        free(root);
    }
}
