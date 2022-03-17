#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/data_structures/red_black_trees.h"

/**
 ** @file red_black_trees.c
 ** @brief Red-Black Trees implementation
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Rotate the tree to the left
 ** @param T the tree to rotate in
 ** @param x the node to rotate
 **/
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
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

/**
 ** @brief Rotate the tree to the right
 ** @param T the tree to rotate in
 ** @param x the node to rotate
 **/
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
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

/* This horrible "(*z)->" thing is due to the fact that, if you want to edit a pointer... you have to pass its pointer */
// void RBTInsertFixupLeft(RBTTree *T, RBTNode **z) {
//     RBTNode *y = (*z)->parent->right;
// 
//     if (y->color == RED) {
//         (*z)->parent->color = BLACK;
//         y->color = BLACK;
//         (*z)->parent->parent->color = RED;
//         *z = (*z)->parent->parent;
//     } else {
//         if (*z == (*z)->parent->right) {
//             *z = (*z)->parent;
//             RBTLeftRotate(T, *z);
//         }
// 
//         (*z)->parent->color = BLACK;
//         (*z)->parent->parent->color = RED;
// 
//         RBTRightRotate(T, (*z)->parent->parent);
//     }
// }

// void RBTInsertFixupRight(RBTTree *T, RBTNode *z) {
//     RBTNode *y = z->parent->parent->left;
// 
//     if (y->color == RED) {
//         z->parent->color = BLACK;
//         y->color = BLACK;
//         z->parent->parent->color = RED;
//         z = z->parent->parent;
//     } else {
//         if (z == z->parent->left) {
//             z = z->parent;
//             RBTRightRotate(T, z);
//         }
// 
//         z->parent->color = BLACK;
//         z->parent->parent->color = RED;
// 
//         RBTLeftRotate(T, z->parent->parent);
//     }
// }

/**
 ** @brief Fix the tree after an insertion
 ** @param T the tree to fix
 ** @param x the node to fix from
 **/
void RBTInsertFixup(RBTTree *T, RBTNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            /* Fixup Left */
            RBTNode *y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    RBTLeftRotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                RBTRightRotate(T, z->parent->parent);
            }
        } else {
            /* Fixup Right */
            RBTNode *y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RBTRightRotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                RBTLeftRotate(T, z->parent->parent);
            }
        }
    }

    T->root->color = BLACK;
}

/**
 ** @brief Insert a node in the tree
 ** @param T the tree to insert in
 ** @param z the node to insert
 **/
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

    z->parent = y;

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

    RBTInsertFixup(T, z);

    T->cardinality += 1;
}

/**
 ** @brief Create a new node
 ** @param T the tree to insert in
 ** @param k the key to insert
 ** @return node containing the key
 **/
RBTNode *RBTNewNode(RBTTree *T, int k) {
    RBTNode *node = malloc(sizeof(RBTNode));

    node->parent = T->nil;
    node->left = T->nil;
    node->right = T->nil;
    node->color = RED;
    node->key = k;

    return node;
}

/**
 ** @brief Insert a key in the tree
 ** @param T the tree to insert in
 ** @param key the key to insert
 **/
void RBTInsertKey(RBTTree *T, int key) {
    RBTNode *x = RBTNewNode(T, key);

    RBTInsert(T, x);
}

/**
 ** @brief Transplant a node
 ** @param T the tree where the transplant occurs
 ** @param u the node to transplant
 ** @param v the node to transplant with
 ** @return node containing the key
 **/
void RBTTransplant(RBTTree *T, RBTNode *u, RBTNode *v) {
    if (u->parent == T->nil) {
        T->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

// void RBTDeleteFixupLeft(RBTTree *T, RBTNode *x) {
//     RBTNode *w = x->parent->right;
// 
//     if (w->color == RED) {
//         w->color = BLACK;
//         x->parent->color = RED;
//         RBTLeftRotate(T, x->parent);
//         w = x->parent->right;
//     }
// 
//     if (w->left->color == BLACK && w->right->color == BLACK) {
//         w->color = RED;
//         x = x->parent;
//     } else {
//         if (w->right->color == BLACK) {
//             w->left->color = BLACK;
//             w->color = RED;
//             RBTRightRotate(T, w);
//             w = x->parent->right;
//         }
// 
//         w->color = x->parent->color;
//         x->parent->color = BLACK;
//         w->right->color = BLACK;
//         RBTLeftRotate(T, x->parent);
//         x = T->root;
//     }
// }

// void RBTDeleteFixupRight(RBTTree *T, RBTNode *x) {
//     RBTNode *w = x->parent->left;
// 
//     if (w->color == RED) {
//         w->color = BLACK;
//         x->parent->color = RED;
//         RBTRightRotate(T, x->parent);
//         w = x->parent->left;
//     }
// 
//     if (w->right->color == BLACK && w->left->color == BLACK) {
//         w->color = RED;
//         x = x->parent;
//     } else {
//         if (w->left->color == BLACK) {
//             w->right->color = BLACK;
//             w->color = RED;
//             RBTLeftRotate(T, w);
//             w = x->parent->left;
//         }
// 
//         w->color = x->parent->color;
//         x->parent->color = BLACK;
//         w->left->color = BLACK;
//         RBTRightRotate(T, x->parent);
//         x = T->root;
//     }
// }

/**
 ** @brief Fix the tree after a deletion
 ** @param T the tree to fix
 ** @param x the node to fix
 **/
void RBTDeleteFixup(RBTTree *T, RBTNode *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            /* Delete Fixup Left */
            RBTNode *w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RBTLeftRotate(T, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RBTRightRotate(T, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RBTLeftRotate(T, x->parent);
                x = T->root;
            }
        } else {
            /* Delete Fixup Right */
            RBTNode *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RBTRightRotate(T, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    RBTLeftRotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RBTRightRotate(T, x->parent);
                x = T->root;
            }
        }
    }

    x->color = BLACK;
}

/**
 ** @brief Search the minimum node of a subtree
 ** @param T the tree to search in
 ** @param x the node to start the search from
 ** @return node containing the minimum key
 **/
RBTNode *RBTMinimum(RBTTree *T, RBTNode *x) {
    while (x->left != T->nil) {
        x = x->left;
    }

    return x;
}

/**
 ** @brief Delete a node from the tree
 ** @param T the tree to delete from
 ** @param z the node to delete
 **/
void RBTDelete(RBTTree *T, RBTNode *z) {
    RBTNode *y = z;
    Color y_original_color = y->color;

    RBTNode *x;

    if (z->left == T->nil) {
        x = z->right;
        RBTTransplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        RBTTransplant(T, z, z->left);
    } else {
        y = RBTMinimum(T, z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            RBTTransplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        RBTTransplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) {
        RBTDeleteFixup(T, x);
    }

    T->cardinality -= 1;

    free(z);
    z = NULL;
}

// RBTNode *RBTSearch(RBTTree *T, RBTNode *x, int k) {
//     if (x == T->nil || x->key == k) {
//         return x;
//     }
// 
//     if (k < x->key) {
//         return RBTSearch(T, x->left, k);
//     } else {
//         return RBTSearch(T, x->right, k);
//     }
// }

/**
 ** @brief Iteratively search for a key in the tree
 ** @param T the tree to search in
 ** @param x the node to start the search from
 ** @param k the key to search for
 ** @return node containing the key
 **/
RBTNode *RBTIterativeSearch(RBTTree *T, RBTNode *x, int k) {
    while (x != T->nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x;
}

/**
 ** @brief Delete a key from the tree
 ** @param T the tree to delete from
 ** @param key the key to delete
 ** @return true if the key was found and deleted, false otherwise
 **/
bool RBTDeleteKey(RBTTree *T, int k) {
    RBTNode *x = RBTIterativeSearch(T, T->root, k);

    if (x != T->nil) {
        RBTDelete(T, x);
        return true;
    } else {
        return false;
    }
}

/**
 ** @brief Empty the tree
 ** @param T the tree to empty
 ** @param x the node to start the deletion from
 **/
void RBTEmptyTree(RBTTree *T, RBTNode *x) {
    if (x != T->nil && x != NULL) {
        RBTEmptyTree(T, x->left);
        RBTEmptyTree(T, x->right);
        free(x);
        x = NULL;
    }
}

// void RBTEmptyTreePreserveStructure(RBTTree *T, RBTNode *x) {
//     if (x != T->nil && x != NULL) {
//         RBTEmptyTreePreserveStructure(T, x->left);
//         RBTEmptyTreePreserveStructure(T, x->right);
//         RBTDelete(T, x);
//     }
// }

/**
 ** @brief Destroy the tree
 ** @param T the tree to destroy
 **/
void RBTDestroyTree(RBTTree *T) {
    RBTEmptyTree(T, T->root);

    free(T->nil);
    T->nil = NULL;

    free(T);
    T = NULL;
}

/**
 ** @brief Create a new tree
 ** @param x the node to insert (can be NULL)
 ** @return address of the new tree
 **/
RBTTree *RBTNewTree(RBTNode *x) {
    RBTTree *tree = malloc(sizeof(RBTTree));

    RBTNode *nil = malloc(sizeof(RBTNode));
    nil->color = BLACK;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->key = -1; // distinguishable value (I will only insert positive values)

    tree->nil = nil;

    if (x != NULL) {
        tree->root = x;
        tree->cardinality = 1;
    } else {
        tree->root = tree->nil;
        tree->cardinality = 0;
    }

    return tree;
}
