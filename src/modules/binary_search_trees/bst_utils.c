#include "../../headers/binary_search_trees/binary_search_trees.h"
#include "../../headers/binary_search_trees/bst_utils.h"

void BSTInOrderTreeWalkToArray(BSTNode *x, int array[], size_t *index) {
    if (x != NULL) {
        BSTInOrderTreeWalkToArray(x->left_child, array, index);
        array[*index] = x->key, (*index)++;
        BSTInOrderTreeWalkToArray(x->right_child, array, index);
    }
}
