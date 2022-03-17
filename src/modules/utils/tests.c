#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/utils/tests.h"
#include "../../headers/utils/utils.h"

bool test_linked_list() {
    LLHead *L = LLNewList(NULL);

    int *rand_insert_values_pool = gen_rnd_array(10000);
    int *rand_search_values_pool = gen_rnd_array(6000);
    int *rand_delete_values_pool = gen_rnd_array(4000);

    for (int i = 0; i < 10000; i++) {
        LLInsertKey(L, rand_insert_values_pool[i]);
    }

    for (int i = 0; i < 6000; i++) {
        LLSearch(L, rand_search_values_pool[i]);
    }

    int *array = new_array(10000);

    LLListWalkToArray(L, array);

    for (ssize_t i = 0; i < 10000; ++i) {
        if (array[9999 - i] != rand_insert_values_pool[i]) {
            printf("LL: Insertions failed (%d != %d)\n", array[i], rand_insert_values_pool[i]);
            print_array(array, 10000);
            print_array(rand_insert_values_pool, 10000);

            return false;
        }
    }

    for (int i = 0; i < 4000; ++i) {
        LLDeleteKey(L, rand_delete_values_pool[i]);
    }

    LLDestroyList(L);

    free(array);

    free(rand_insert_values_pool);
    free(rand_search_values_pool);
    free(rand_delete_values_pool);

    return true;
}

bool test_binary_search_tree() {
    int *rand_insert_values_pool = gen_rnd_array(10000);
    int *rand_search_values_pool = gen_rnd_array(6000);
    int *rand_delete_values_pool = gen_rnd_array(4000);

    size_t insert_index = 0;
    size_t search_index = 0;
    size_t delete_index = 0;

    BSTTree *T = BSTNewTree(NULL);

    for (size_t key = 0; key < 10000; ++key) {
        BSTInsertKey(T, rand_insert_values_pool[insert_index++]);
    }

    for (size_t key = 0; key < 6000; ++key) {
        BSTIterativeSearch(T->root, rand_search_values_pool[search_index++]);
    }

    for (size_t key = 0; key < 4000; ++key) {
        BSTDeleteKey(T, rand_delete_values_pool[delete_index++]);
    }

    int *array = new_array(T->cardinality);
    size_t index = 0;

    BSTInOrderTreeWalkToArray(T->root, array, &index);

    if (!is_sorted(array, T->cardinality)) {
        fprintf(stderr, "BST: The array was not sorted correctly.\n");
        print_array(array, T->cardinality);

        return false;
    }

    free(array);

    BSTDestroyTree(T);

    free(rand_insert_values_pool);
    free(rand_search_values_pool);
    free(rand_delete_values_pool);

    return true;
}

ssize_t RBTComputeHeight(RBTTree *T, RBTNode *x) {
    if (x == T->nil) return 0;

    ssize_t lh = RBTComputeHeight(T, x->left);
    ssize_t rh = RBTComputeHeight(T, x->right);

    if (lh == -1 || rh == -1 || lh != rh) {
        return -1;
    } else {
        return lh + (x->color == BLACK ? 1 : 0);
    }
}

bool test_RB_properties(RBTTree *T, int *array, size_t array_size) {
    if (T->root == T->nil) return true;

    if (T->root->color != BLACK) {
        fprintf(stderr, "RBT: Root is not black.\n");

        return false;
    }

    if (RBTComputeHeight(T, T->root) == -1) {
        fprintf(stderr, "RBT: The tree is not balanced.\n");

        return false;
    }

    if (T->nil->color != BLACK) {
        fprintf(stderr, "RBT: T.nil is not black.\n");

        return false;
    }

    for (size_t i = 0; i < array_size; ++i) {
        RBTNode *x = RBTIterativeSearch(T, T->root, array[i]);

        if (x == NULL) continue;

        if ((x->color == RED &&
             ((x->left->color == RED || x->right->color == RED) ||
              (x->left->color == RED && x->right->color == BLACK) ||
              (x->left->color == BLACK && x->right->color == RED))) ||
            (x->color != RED && x->color != BLACK)) {
            fprintf(stderr, "RBT: bad RBT (2+ consecutive red nodes).\n");

            return false;
        }
    }

    return true;
}

bool test_red_black_tree() {
    int *rand_insert_values_pool = gen_rnd_array(10000);
    int *rand_search_values_pool = gen_rnd_array(6000);
    int *rand_delete_values_pool = gen_rnd_array(4000);

    size_t insert_index = 0;
    size_t search_index = 0;
    size_t delete_index = 0;

    RBTTree *T = RBTNewTree(NULL);

    for (size_t key = 0; key < 10000; ++key) {
        RBTInsertKey(T, rand_insert_values_pool[insert_index++]);
    }

    for (size_t key = 0; key < 6000; ++key) {
        RBTIterativeSearch(T, T->root, rand_search_values_pool[search_index++]);
    }

    for (size_t key = 0; key < 4000; ++key) {
        RBTDeleteKey(T, rand_delete_values_pool[delete_index++]);
    }

    int *array = new_array(T->cardinality);
    size_t index = 0;

    RBTInOrderTreeWalkToArray(T, T->root, array, &index);

    if (!is_sorted(array, T->cardinality)) {
        fprintf(stderr, "RBT: The array was not sorted correctly.\n");
        print_array(array, T->cardinality);
    }

    free(array);

    if (!test_RB_properties(T, rand_insert_values_pool, 10000)) {
        fprintf(stderr, "RBT: The tree is not a valid RBT.\n");
    }

    RBTDestroyTree(T);

    free(rand_insert_values_pool);
    free(rand_search_values_pool);
    free(rand_delete_values_pool);

    return true;
}

bool test_b_tree() {
    int *rand_insert_values_pool = gen_rnd_array(10000);
    int *rand_search_values_pool = gen_rnd_array(6000);
    int *rand_delete_values_pool = gen_rnd_array(4000);

    size_t insert_index = 0;
    size_t search_index = 0;
    size_t delete_index = 0;

    BTTree *T = BTNewTree(100);

    for (size_t key = 0; key < 10000; ++key) {
        BTInsertKey(T, rand_insert_values_pool[insert_index++]);
    }

    for (size_t key = 0; key < 6000; ++key) {
        BTSearchKey(T->root, rand_search_values_pool[search_index++]);
    }

    for (size_t key = 0; key < 4000; ++key) {
        BTDeleteKey(T, rand_delete_values_pool[delete_index++]);
    }

    BTDestroyTree(T);

    free(rand_insert_values_pool);
    free(rand_search_values_pool);
    free(rand_delete_values_pool);

    return true;
}

bool run_tests() {
    bool result = true;

    result &= test_linked_list();
    result &= test_binary_search_tree();
    result &= test_red_black_tree();
    result &= test_b_tree();

    return result;
}
