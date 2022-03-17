#include <stdlib.h>

#include "../../headers/data_structures/binary_search_trees.h"

/**
 ** @file binary_search_trees.c
 ** @brief Binary Search Trees implementation
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Search recursively a key
 ** @param x node where to start the search
 ** @param k key to search
 ** @return node containing the key or NULL if not found
 **/
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

/**
 ** @brief Search iteratively a key
 ** @param x node where to start the search
 ** @param k key to search
 ** @return node containing the key or NULL if not found
 **/
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

/**
 ** @brief Find the minimum key in the tree
 ** @param x node where to start the search
 ** @return node containing the key
 **/
BSTNode *BSTMinimum(BSTNode *x) {
    while (x->left != NULL) {
        x = x->left;
    }

    return x;
}

/**
 ** @brief Find the maximum key in the tree
 ** @param x node where to start the search
 ** @return node containing the key
 **/
BSTNode *BSTMaximum(BSTNode *x) {
    while (x->right != NULL) {
        x = x->right;
    }

    return x;
}

/**
 ** @brief Find the successor of a key
 ** @param x node where to start the search
 ** @return node containing the key
 **/
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

/**
 ** @brief Find the predecessor of a key
 ** @param x node where to start the search
 ** @return node containing the key
 **/
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

/**
 ** @brief Create a node
 ** @param k key to insert
 ** @return node containing the key
 **/
BSTNode *BSTNewNode(int k) {
    BSTNode *node = malloc(sizeof(BSTNode));

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = k;

    return node;
}

/**
 ** @brief Insert a node in the tree
 ** @param T tree to insert the node
 ** @param z node to insert
 **/
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

/**
 ** @brief Insert a key in the tree
 ** @param T tree to insert the key
 ** @param k key to insert
 **/
void BSTInsertKey(BSTTree *T, int k) {
    BSTNode *z = BSTNewNode(k);

    BSTInsert(T, z);
}

/**
 ** @brief Create a tree
 ** @param x node to insert, can be NULL if the tree is empty
 ** @return tree's address in memory
 **/
BSTTree *BSTNewTree(BSTNode *x) {
    BSTTree *tree = malloc(sizeof(BSTTree));

    if (x != NULL) {
        tree->root = x; // if a BSTNode was supplied, we save it in the root

        tree->cardinality = 1;
    } else {
        tree->root = NULL;

        tree->cardinality = 0;
    }

    return tree;
}

/**
 ** @brief Transplant a node
 ** @param T tree to transplant the node
 ** @param u node to transplant (source)
 ** @param v node to transplant (destination)
 **/
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

/**
 ** @brief Delete a node from the tree
 ** @param T tree to delete the node
 ** @param z node to delete
 **/
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

/**
 ** @brief Delete a key from the tree
 ** @param T tree to delete the key
 ** @param k key to delete
 **/
void BSTDeleteKey(BSTTree *T, int k) {
    BSTNode *z = BSTIterativeSearch(T->root, k);

    if (z != NULL) BSTDelete(T, z);
}

/**
 ** @brief Destroy a tree and free the memory
 ** @param T tree to destroy
 ** @param x next node to destroy
 **/
void BSTEmptyTree(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left);
        BSTEmptyTree(T, x->right);
        free(x);
    }
}

/**
 ** @brief Destroy a tree but maintain it a valid BST while freeing the memory
 ** @param T tree to destroy
 ** @param x next node to destroy
 **/
void BSTEmptyTreePreserveStructure(BSTTree *T, BSTNode *x) {
    if (x != NULL) {
        BSTEmptyTree(T, x->left);
        BSTEmptyTree(T, x->right);
        BSTDelete(T, x);
    }
}

/**
 ** @brief Destroy a tree
 ** @param T tree to destroy
 **/
void BSTDestroyTree(BSTTree *T) {
    BSTEmptyTree(T, T->root);

    free(T);
    T = NULL;
}
