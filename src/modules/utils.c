#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../headers/utils.h"
#include "../headers/data_structures/linked_lists.h"
#include "../headers/data_structures/binary_search_trees.h"

// Generate a new, uninitialized, array of integers, given its length
int *new_array(const size_t length) {
    int *array = malloc(length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Error: couldn't allocate %zu-cells array, size: %zu bytes).\n", length,
                length * sizeof(int));
        exit(EXIT_FAILURE);
    }

    return array;
}

// Generate a new random array, given its length
int *gen_rnd_array(const size_t length) {
    int *array = malloc(length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Error: couldn't allocate %zu-cells array, size: %zu bytes).\n", length,
                length * sizeof(int));
        exit(EXIT_FAILURE);
    }

    for (size_t index = 0; index < length; ++index)
        array[index] = rand() % (int) length; // random value between 0 and `length` (0 <= value < length)

    return array;
}

// Check if a given array is sorted (ascending order)
// This is an antagonist function that ensures that
// the sorting algorithms work properly.
bool is_sorted(const int array[], size_t length) {
    for (size_t i = 1; i < length; ++i)
        if (array[i - 1] > array[i])
            return false;

    return true;
}

// Prints to stdout a given array
void print_array(const int array[], size_t length) {
    for (size_t i = 0; i < length; ++i)
        printf("%s%d%s", i == 0 ? "[" : "", array[i], i < length - 1 ? ", " : "]\n");
}

// Deallocate and set to NULL some memory referenced by a pointer - I'll use this for the arrays
void DeallocNullifyInt(int *array) {
    free(array);
    array = NULL;
}

void LLListWalkToArray(LLHead *L, int array[]) {
    LLNode *x = L->head;

    size_t index = 0;
    while (x != NULL) {
        array[index++] = x->key;
        x = x->next;
    }
}

void BSTInOrderTreeWalkToArray(BSTNode *x, int array[], size_t *index) {
    if (x != NULL) {
        BSTInOrderTreeWalkToArray(x->left_child, array, index);
        array[*index] = x->key, (*index)++;
        BSTInOrderTreeWalkToArray(x->right_child, array, index);
    }
}
