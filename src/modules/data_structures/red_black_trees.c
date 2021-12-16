#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
        x->parent->left = y;
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
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void RBTInsertFixupLeft(RBTTree *T, RBTNode *z) {
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
}

void RBTInsertFixupRight(RBTTree *T, RBTNode *z) {
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

void RBTInsertFixup(RBTTree *T, RBTNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTInsertFixupLeft(T, z);
        } else {
            RBTInsertFixupRight(T, z);
        }
    }

    T->root->color = BLACK;
}

void TESTInsertFixup(RBTTree *T, RBTNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
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
    //TInsertFixup(T, z);

    T->cardinality += 1;
}

RBTNode *RBTNewNode(RBTTree *T, int k) {
    RBTNode *node = malloc(sizeof(RBTNode));

    node->parent = T->nil;
    node->left = T->nil;
    node->right = T->nil;
    node->color = RED;
    node->key = k;

    return node;
}

void RBTInsertKey(RBTTree *T, int key) {
    RBTNode *x = RBTNewNode(T, key);

    RBTInsert(T, x);
}

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

void RBTDeleteFixupLeft(RBTTree *T, RBTNode *z) {
    RBTNode *w = z->parent->right;

    if (w->color == RED) {
        w->color = BLACK;
        z->parent->color = RED;
        RBTLeftRotate(T, z->parent);
        w = z->parent->right;
    }

    if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        z = z->parent;
    } else {
        if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            RBTRightRotate(T, w);
            w = z->parent->right;
        }

        w->color = z->parent->color;
        z->parent->color = BLACK;
        w->right->color = BLACK;
        RBTLeftRotate(T, z->parent);
        z = T->root;
    }
}

void RBTDeleteFixupRight(RBTTree *T, RBTNode *z) {
    RBTNode *w = z->parent->left;

    if (w->color == RED) {
        w->color = BLACK;
        z->parent->color = RED;
        RBTRightRotate(T, z->parent);
        w = z->parent->right;
    }

    if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        z = z->parent;
    } else {
        if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            RBTLeftRotate(T, w);
            w = z->parent->left;
        }

        w->color = z->parent->color;
        z->parent->color = BLACK;
        w->left->color = BLACK;
        RBTRightRotate(T, z->parent);
        z = T->root;
    }
}

void RBTDeleteFixup(RBTTree *T, RBTNode *x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBTDeleteFixupLeft(T, x);
        } else {
            RBTDeleteFixupRight(T, x);
        }
    }

    x->color = BLACK;
}

RBTNode *RBTMinimum(RBTTree *T, RBTNode *x) {
    while (x->left != T->nil) {
        x = x->left;
    }

    return x;
}

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

RBTNode *RBTSearch(RBTTree *T, RBTNode *x, int k) {
    if (x == T->nil || x->key == k) {
        return x;
    }

    if (k < x->key) {
        return RBTSearch(T, x->left, k);
    } else {
        return RBTSearch(T, x->right, k);
    }
}

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

bool RBTDeleteKey(RBTTree *T, int k) {
    RBTNode *x = RBTIterativeSearch(T, T->root, k);

    if (x != T->nil && x != NULL) {
        RBTDelete(T, x);

        return true;
    } else {
        return false;
    }
}

void RBTRecursiveEmptyTree(RBTTree *T, RBTNode *x) {
    if (x != T->nil && x != NULL) {
        RBTRecursiveEmptyTree(T, x->left);
        RBTRecursiveEmptyTree(T, x->right);
        free(x);
        x = NULL;
    }
}

void RBTEmptyTreePreserveStructure(RBTTree *T, RBTNode *x) {
    if (x != T->nil && x != NULL) {
        RBTRecursiveEmptyTree(T, x->left);
        RBTRecursiveEmptyTree(T, x->right);
        RBTDelete(T, x);
    }
}

void RBTDestroyTree(RBTTree *T) {
    RBTRecursiveEmptyTree(T, T->root);

    free(T->nil);
    T->nil = NULL;

    free(T);
    T = NULL;
}

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
