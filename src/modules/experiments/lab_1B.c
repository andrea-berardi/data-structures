#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/utils/utils.h"
#include "../../headers/utils/experiments.h"

long double
exp_1B(size_t max_keys, size_t max_search, size_t max_delete, size_t max_instances, DataStructure data_structure) {
    clock_t t_tot = 0;

    for (size_t instance = 1; instance <= max_instances; ++instance) {
        clock_t t_start, t_end;

        // I'm creating these arrays of random integer values for many reasons:
        // - I can keep track of what I'm generating
        // - I won't be adding any overheads by using the modulus operator (%) during the experiments
        // - By using "small" values I'll be able to tell if weird things are happening to my arrays
        // - I'll be able to compare the generated arrays and the generated trees more easily
        // Also, I'm using different arrays in order not to create outliers.
        int *rand_insert_values_pool = gen_rnd_array(max_keys);
        int *rand_search_values_pool = gen_rnd_array(max_search);
        int *rand_delete_values_pool = gen_rnd_array(max_delete);

        // I'll use these indexes to scan the arrays. They'll be incremented at each run.
        size_t insert_index = 0;
        size_t search_index = 0;
        size_t delete_index = 0;

        // I'm declaring these here so that I can run debug checks on them before returning
        BSTTree *T = BSTNewTree(NULL);
        LLHead *L = LLNewList(NULL);

        switch (data_structure) {
            case BST: {
                t_start = clock();
                for (size_t key = 0; key < max_keys; ++key) {
                    // it's important to use `i++` instead of `++i`
                    BSTInsertKey(T, rand_insert_values_pool[insert_index++]);
                }

                for (size_t key = 0; key < max_search; ++key) {
                    // it's important to use `i++` instead of `++i`
                    BSTIterativeSearch(T->root, rand_search_values_pool[search_index++]);
                }

                for (size_t key = 0; key < max_delete; ++key) {
                    // This uses the iterative version of BSTSearch, but both versions are implemented and functional.
                    // I can't see any performance differences between the two, but the iterative version should be the go-to choice.
                    BSTDeleteKey(T, rand_delete_values_pool[delete_index++]);
                }
                t_end = clock();

                break;
            }

            case LL: {
                t_start = clock();
                for (size_t key = 0; key < max_keys; ++key) {
                    // it's important to use `i++` instead of `++i`
                    LLInsertKey(L, rand_insert_values_pool[insert_index++]);
                }

                for (size_t key = 0; key < max_search; ++key) {
                    // it's important to use `i++` instead of `++i`
                    LLSearch(L, rand_search_values_pool[search_index++]);
                }

                for (size_t key = 0; key < max_delete; ++key) {
                    // This uses the iterative version of BSTSearch, but both versions are implemented and functional.
                    // I can't see any performance differences between the two, but the iterative version should be the go-to choice.
                    LLDeleteKey(L, rand_delete_values_pool[delete_index++]);
                }
                t_end = clock();

                break;
            }

            default: {
                fprintf(stderr, "Unknown data_structure `%d`\n", data_structure);

                exit(EXIT_FAILURE);
            }
        }

        t_tot += t_end - t_start;

        /* The following lines will give back to the OS the dynamic memory previously allocated */

        // Destroying the data structures of the test
        BSTDestroyTree(T); // destroying the tree and all its leaves (nodes) - `T` is now NULL
        LLDestroyList(L); // destroying the list and all its nodes - `L` is now NULL

        // Destroying the arrays
        free(rand_insert_values_pool);
        free(rand_search_values_pool);
        free(rand_delete_values_pool);
    }

    return (long double) t_tot / (long double) max_instances;
}

void lab_1B(char file[], Configuration conf) {
    FILE *fp = fopen(file, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file `%s`\n", file);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Keys (n),Binary Search Trees,Linked Lists\n");
    for (size_t keys = conf.min_keys; keys <= conf.max_keys; keys += conf.step) {
        srand(conf.seed);

        size_t max_search = keys * conf.search_delete_ratio / 100;
        size_t max_delete = keys - max_search;

        srand(conf.seed);
        long double time_BST = exp_1B(keys, max_search, max_delete, conf.max_instances, BST);
        srand(conf.seed);
        long double time_LL = exp_1B(keys, max_search, max_delete, conf.max_instances, LL);

        fprintf(fp, "%zu,%Lf,%Lf\n", keys, time_BST, time_LL);

        ++conf.seed;
    }

    if (fclose(fp) == EOF)
        fprintf(stderr, "Failed to flush buffered data on `%s`\n", file);
}
