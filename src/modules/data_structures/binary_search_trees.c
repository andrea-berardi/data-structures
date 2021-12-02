#include <stdlib.h>

#include "../../headers/data_structures/binary_search_trees.h"

BSTNode *BSTSearch(BSTNode *x, int k) {
    if (x == NULL || x->key == k) {
        return x;
    }

    if (k < x->key) {
        return BSTSearch(x->left, k);
    } else {
        return BSTSearch(x->right, k);
    }
}

BSTNode *BSTIterativeSearch(BSTNode *x, int k) {
    while (x != NULL && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x;
}

BSTNode *BSTMinimum(BSTNode *x) {
    while (x->left != NULL) {
        x = x->left;
    }

    return x;
}

BSTNode *BSTMaximum(BSTNode *x) {
    while (x->right != NULL) {
        x = x->right;
    }

    return x;
}

BSTNode *BSTSuccessor(BSTNode *x) {
    if (x->right != NULL) {
        return BSTMinimum(x->right);
    }

    BSTNode *y = x->parent;

    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }

    return y;
}

BSTNode *BSTPredecessor(BSTNode *x) {
    if (x->left != NULL) {
        return BSTMaximum(x->left);
    }

    BSTNode *y = x->parent;

    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }

    return y;
}

BSTNode *BSTNewNode(int k) {
    BSTNode *node = malloc(sizeof(BSTNode));

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = k;

    return node;
}

void BSTInsert(BSTTree *T, BSTNode *z) {
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
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == NULL) {
        T->root = z; // The Tree was empty
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

void BSTInsertKey(BSTTree *T, int k) {
    BSTNode *z = BSTNewNode(k);

    BSTInsert(T, z);
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
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

void BSTDelete(BSTTree *T, BSTNode *z) {
    if (z->left == NULL) {
        BSTTransplant(T, z, z->right);
    } else if (z->right == NULL) {
        BSTTransplant(T, z, z->left);
    } else {
        BSTNode *y = BSTMinimum(z->right);

        if (y->parent != z) {
            BSTTransplant(T, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        BSTTransplant(T, z, y);

        y->left = z->left;
        y->left->parent = y;
    }

    T->cardinality -= 1; // we decrease the number of elements in our tree

    free(z);
    z = NULL;
}

void BSTDeleteKey(BSTTree *T, int k) {
    BSTNode *z = BSTIterativeSearch(T->root, k);

    if (z != NULL) BSTDelete(T, z);
}

// this procedure destroys every node of a tree (faster than `BSTEmptyTreePreserveStructure()`)
// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTEmptyTree(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left);
        BSTEmptyTree(T, x->right);
        free(x);
    }
}

// this procedure destroys every node of a tree BUT preserves the structure of the BST while running
// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTEmptyTreePreserveStructure(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left);
        BSTEmptyTree(T, x->right);
        BSTDelete(T, x);
    }
}

// this is basically a TreePostOrderWalk that instead of printing the key destroys the node, and the whole BST
void BSTDestroyTree(BSTTree *T) {
    BSTEmptyTree(T, T->root);

    free(T);
    T = NULL;
}
