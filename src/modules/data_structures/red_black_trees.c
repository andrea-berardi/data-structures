#include "../../headers/data_structures/red_black_trees.h"

void RBTLeftRotate(RBTTree *T, RBTNode *x) {
    RBTNode *y = x->right;
    x->right = y->left;

    if (y->left != T->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == T->nil) {
        T->root = y;
    } else if (x == x->parent->left) {
        y->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RBTRightRotate(RBTTree *T, RBTNode *x) {
    RBTNode *y = x->left;
    x->left = y->right;

    if (y->right != T->nil) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == T->nil) {
        T->root = y;
    } else if (x == x->parent->right) {
        y->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void RBTInsert(RBTTree *T, RBTNode *z) {
    RBTNode *y = T->nil;
    RBTNode *x = T->root;

    while (x != T->nil) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    if (y == T->nil) {
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    // RBTTreeInsertFixup()
}
