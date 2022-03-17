#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/data_structures/b_trees.h"

/**
 ** @file b_trees.c
 ** @brief B-Trees implementation
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Simulate writing a node on disk
 ** @param node the node to write
 ** @return address of the node
 **/
BTNode *DiskWrite(BTNode *node) {
    return node;
}

/**
 ** @brief Simulate reading a node from disk
 ** @param xci the node read
 ** @return address of the node
 **/
BTNode *DiskRead(BTNode *xci) {
    return xci;
}

/**
 ** @brief Create a new node
 ** @param t t of the tree
 ** @param leaf is the node a leaf?
 ** @return address of the node
 **/
BTNode *BTNewNode(ssize_t t, bool leaf) {
    BTNode *x = malloc(sizeof(BTNode));

    x->n = 0; // number of keys - cardinality
    x->leaf = leaf; // will be determined by the function call, if provided
    x->keys = malloc(sizeof(int) * 2 * t - 1); // array of keys of the node
    x->children = malloc(sizeof(BTNode) * (2 * t)); // array of children of the node

    return x;
}

/**
 ** @brief Create a new tree
 ** @param t t of the tree
 ** @return address of the tree
 **/
BTTree *BTNewTree(ssize_t t) {
    BTTree *tree = malloc(sizeof(BTTree));

    tree->t = t; // starting capacity

    tree->root = BTNewNode(t, true);
    tree->root->n = 0; // root cardinality
    tree->root->leaf = true; // root is a leaf

    DiskWrite(tree->root);

    return tree;
}

/**
 ** @brief Split a node
 ** @param T the tree that contains the node to split
 ** @param x the node to split
 ** @param i the index of the key to split
 **/
void BTSplitChild(BTTree *T, BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = BTNewNode(T->t, y->leaf);

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
}

/**
 ** @brief Insert a key in a tree where its node is not full
 ** @param T the tree to insert the key
 ** @param x the node to insert the key
 ** @param k the key to insert
 **/
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

/**
 ** @brief Insert a key in a tree
 ** @param T the tree to insert the key in
 ** @param k the key to insert
 **/
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

/**
 ** @brief Search a key in a tree
 ** @param x the node to search the key in
 ** @param k the key to search
 ** @return struct containing the key and the node where the key is found
 **/
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

/**
 ** @brief Delete a key from a leaf node
 ** @param x the node to delete the key from
 ** @param i the index of the key to delete
 **/
void BTDeleteFromLeaf(BTNode *x, ssize_t i) {
    for (ssize_t j = i + 1; j < x->n; ++j) {
        x->keys[j - 1] = x->keys[j];
    }

    x->n -= 1;

    DiskWrite(x);
}

/**
 ** @brief Find the index of the closest key to the right
 ** @param x the node to search the key in
 ** @param k the key to search
 ** @return the index of the closest key to the right
 **/
ssize_t BTFindKey(BTNode *x, int k) {
    ssize_t i = 0;

    while (i < x->n && k > x->keys[i]) i += 1;

    return i;
}

/**
 ** @brief Predecessor of a key
 ** @param x the node to search the key in
 ** @param i the index of the key to search
 ** @return value of the predecessor of the key
 **/
int BTPredecessor(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];

    while (y->leaf == false) {
        y = y->children[y->n];
    }

    return y->keys[y->n - 1];
}

/**
 ** @brief Successor of a key
 ** @param x the node to search the key in
 ** @param i the index of the key to search
 ** @return value of the successor of the key
 **/
int BTSuccessor(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i + 1];

    while (y->leaf == false) {
        y = y->children[0];
    }

    return y->keys[0];
}

/**
 ** @brief Borrow a key from the previous sibling
 ** @param x the node that borrows the key
 ** @param i the index of the key to pick
 **/
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

    x->keys[i - 1] = z->keys[z->n - 1];

    y->n += 1;
    z->n -= 1;

    DiskWrite(y);
    DiskWrite(z);
    DiskWrite(x);
}

/**
 ** @brief Borrow a key from the successive sibling
 ** @param x the node that borrows the key
 ** @param i the index of the key to search
 **/
void BTBorrowFromNext(BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i + 1];

    y->keys[y->n] = x->keys[i];

    if (y->leaf == false) {
        y->children[y->n + 1] = z->children[0];
    }

    x->keys[i] = z->keys[0];

    for (ssize_t j = 1; j < z->n; ++j) {
        z->keys[j - 1] = z->keys[j];
    }

    if (z->leaf == false) {
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

/**
 ** @brief Merge a node with its next sibling
 ** @param T the tree that contains the nodes
 ** @param x the node to merge
 ** @param i the index of the node to merge
 **/
void BTMerge(BTTree *T, BTNode *x, ssize_t i) {
    BTNode *y = x->children[i];
    BTNode *z = x->children[i + 1];

    y->keys[T->t - 1] = x->keys[i];

    for (ssize_t j = 0; j < z->n; ++j) {
        y->keys[T->t + j] = z->keys[j];
    }

    if (y->leaf == false) {
        for (ssize_t j = 0; j <= z->n; ++j) {
            y->children[T->t + j] = z->children[j];
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

    free(z->keys);
    z->keys = NULL;

    free(z->children);
    z->children = NULL;

    free(z);
    z = NULL;
}

/**
 ** @brief Fill a node with keys from its previous sibling
 ** @param T the tree that contains the nodes
 ** @param x the node to fill
 ** @param i the index of the node to fill
 **/
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

/**
 ** @brief Remove a key from a node
 ** @param T the tree that contains the key to delete
 ** @param x the node to remove the key from
 ** @param key the key to remove
 **/
void BTRemoveFromNode(BTTree *T, BTNode *x, int k);

/**
 ** @brief Delete a key from a node that isn't a leaf
 ** @param T the tree that contains the key to delete
 ** @param x the node to remove the key from
 ** @param i the index of the key to remove
 ** @return value of the predecessor of the key
 **/
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

/**
 ** @brief Remove a key from a node
 ** @param T the tree that contains the key to delete
 ** @param x the node to remove the key from
 ** @param k the key to remove
 **/
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

/**
 ** @brief Delete a key from a tree
 ** @param T the tree to delete the key from
 ** @param k the key to delete
 **/
void BTDeleteKey(BTTree *T, int key) {
    if (T->root == NULL) {
        return; // empty tree
    }

    BTRemoveFromNode(T, T->root, key);

    if (T->root->n == 0) {
        BTNode *tmp_root = T->root;

        if (T->root->leaf == true) {
            T->root = NULL;
        } else {
            T->root = T->root->children[0];
        }

        free(tmp_root->keys);
        free(tmp_root->children);
        free(tmp_root);
        tmp_root = NULL;
    }
}

/**
 ** @brief Destroy a tree and its nodes recursively
 ** @param x the current node to destroy
 **/
void BTDestroyTreeRecursive(BTNode *x) {
    ssize_t i;

    for (i = 0; i < x->n; i++) {
        if (x->leaf == false) {
            BTDestroyTreeRecursive(x->children[i]);
        }
    }

    if (x->leaf == false) {
        BTDestroyTreeRecursive(x->children[i]);
    }

    free(x->keys);
    x->keys = NULL;

    free(x->children);
    x->children = NULL;

    free(x);
    x = NULL;
}

/**
 ** @brief Destroy a tree
 ** @param T the tree to destroy
 **/
void BTDestroyTree(BTTree *T) {
    if (T == NULL || T->root == NULL) {
        return; // empty tree
    }

    BTDestroyTreeRecursive(T->root);

    free(T);
    T = NULL;
}

/**
 ** @brief Print a tree recursively
 ** @param x the current node to print
 **/
void BTTraverseRecurse(BTNode *x) {
    ssize_t i;

    for (i = 0; i < x->n; i++) {
        if (x->leaf == false) {
            BTTraverseRecurse(x->children[i]);
        }

        printf("%d ", x->keys[i]);
    }

    if (x->leaf == false) {
        BTTraverseRecurse(x->children[i]);
    }
}

/**
 ** @brief Traverse a tree
 ** @param T the tree to traverse
 **/
void BTTraverse(BTTree *T) {
    if (T->root == NULL) {
        return;
    }

    BTTraverseRecurse(T->root);

    printf("\n");
}
