#include <stdlib.h>

#include "../../headers/binary_search_trees.h"

BSTNode *BSTTreeSearch(BSTNode *x, int k) {
    if (x == NULL || x->key == k) {
        return x;
    }

    if (k < x->key) {
        return BSTTreeSearch(x->left_child, k);
    } else {
        return BSTTreeSearch(x->right_child, k);
    }
}

BSTNode *BSTIterativeTreeSearch(BSTNode *x, int k) {
    while (x != NULL && k != x->key) {
        if (k < x->key) {
            x = x->left_child;
        } else {
            x = x->right_child;
        }
    }

    return x;
}

BSTNode *BSTTreeMinimum(BSTNode *x) {
    while (x->left_child != NULL) {
        x = x->left_child;
    }

    return x;
}

BSTNode *BSTTreeMaximum(BSTNode *x) {
    while (x->right_child != NULL) {
        x = x->right_child;
    }

    return x;
}

BSTNode *BSTTreeSuccessor(BSTNode *x) {
    if (x->right_child != NULL) {
        return BSTTreeMinimum(x->right_child);
    }

    BSTNode *y = x->parent;

    while (y != NULL && x == y->right_child) {
        x = y;
        y = y->parent;
    }

    return y;
}

BSTNode *BSTTreePredecessor(BSTNode *x) {
    if (x->left_child != NULL) {
        return BSTTreeMaximum(x->left_child);
    }

    BSTNode *y = x->parent;

    while (y != NULL && x == y->left_child) {
        x = y;
        y = y->parent;
    }

    return y;
}

BSTNode *BSTNewNode(int k) {
    BSTNode *node = malloc(sizeof(BSTNode));

    node->parent = NULL;
    node->left_child = NULL;
    node->right_child = NULL;
    node->key = k;

    return node;
}

void BSTTreeInsert(BSTTree *T, BSTNode *z) {
    T->cardinality += 1; // we increase the number of elements in our tree

    if (T->root == NULL) {
        T->root = z;

        return;
    }

    BSTNode *y = NULL;
    BSTNode *x = T->root;

    while (x != NULL) {
        y = x;

        if (z->key < x->key) {
            x = x->left_child;
        } else {
            x = x->right_child;
        }
    }

    z->parent = y;

    if (y == NULL) {
        T->root = z; // The Tree was empty
    } else if (z->key < y->key) {
        y->left_child = z;
    } else {
        y->right_child = z;
    }
}

void BSTTreeInsertKey(BSTTree *T, int k) {
    BSTNode *z = BSTNewNode(k);

    BSTTreeInsert(T, z);
}

BSTTree *BSTNewTree(BSTNode *x) {
    BSTTree *tree = malloc(sizeof(BSTTree));

    if (x != NULL) {
        tree->root = x; // if a BSTNode was supplied, we save it in the root
    } else {
        tree->root = NULL;
    }

    tree->cardinality = 0;

    return tree;
}

void BSTTransplant(BSTTree *T, BSTNode *u, BSTNode *v) {
    if (u->parent == NULL) {
        T->root = v;
    } else if (u == u->parent->left_child) {
        u->parent->left_child = v;
    } else {
        u->parent->right_child = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

void BSTTreeDelete(BSTTree *T, BSTNode *z) {
    if (z->left_child == NULL) {
        BSTTransplant(T, z, z->right_child);
    } else if (z->right_child == NULL) {
        BSTTransplant(T, z, z->left_child);
    } else {
        BSTNode *y = BSTTreeMinimum(z->right_child);

        if (y->parent != z) {
            BSTTransplant(T, y, y->right_child);

            y->right_child = z->right_child;
            y->right_child->parent = y;
        }

        BSTTransplant(T, z, y);

        y->left_child = z->left_child;
        y->left_child->parent = y;
    }

    T->cardinality -= 1; // we decrease the number of elements in our tree

    free(z);
    z = NULL;
}

void BSTTreeDeleteKey(BSTTree *T, int k) {
    BSTNode *z = BSTIterativeTreeSearch(T->root, k);

    if (z != NULL) BSTTreeDelete(T, z);
}

// this procedure destroys every node of a tree (faster than `BSTEmptyTreePreserveStructure()`)
// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTEmptyTree(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left_child);
        BSTEmptyTree(T, x->right_child);
        free(x);
    }
}

// this procedure destroys every node of a tree BUT preserves the structure of the BST while running
// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTEmptyTreePreserveStructure(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left_child);
        BSTEmptyTree(T, x->right_child);
        BSTTreeDelete(T, x);
    }
}

// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTTreeDestroyTree(BSTTree *T) {
    BSTEmptyTree(T, T->root);

    free(T);
    T = NULL;
}
