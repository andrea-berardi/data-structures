#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/utils/utils.h"
#include "../../headers/utils/experiments.h"

long double final_BT(ssize_t t, size_t max_keys, size_t max_search, size_t max_delete, size_t max_instances) {
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
        BTTree *T = BTNewTree(t);

        t_start = clock();
        for (size_t key = 0; key < max_keys; ++key) {
            // it's important to use `i++` instead of `++i`
            BTInsertKey(T, rand_insert_values_pool[insert_index++]);
        }

        for (size_t key = 0; key < max_search; ++key) {
            // it's important to use `i++` instead of `++i`
            BTSearchKey(T->root, rand_search_values_pool[search_index++]);
        }

        for (size_t key = 0; key < max_delete; ++key) {
            // This uses the iterative version of RBTSearch, but both versions are implemented and functional.
            // I can't see any performance differences between the two, but the iterative version should be the go-to choice.
            BTDeleteKey(T, rand_delete_values_pool[delete_index++]); // it's important to use `i++` instead of `++i`
        }
        t_end = clock();

        t_tot += t_end - t_start;

        /* The following lines will give back to the OS the dynamic memory previously allocated */

        // Destroying the data structures of the test
        BTDestroyTree(T);

        // Destroying the arrays
        free(rand_insert_values_pool);
        free(rand_search_values_pool);
        free(rand_delete_values_pool);
    }

    return (long double) t_tot / (long double) max_instances;
}

void lab_final(char file[], Configuration conf) {
    FILE *fp = fopen(file, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file `%s`\n", file);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Keys (n),B-Trees (t = 10),B-Trees (t = 100),B-Trees (t = 1000),\n");
    for (size_t keys = conf.min_keys; keys <= conf.max_keys; keys += conf.step) {
        srand(conf.seed);

        size_t max_search = keys * conf.search_delete_ratio / 100;
        size_t max_delete = keys - max_search;

        long double *array = malloc(10 * sizeof(long double));
        if (array == NULL) {
            fprintf(stderr, "Error: couldn't allocate %d-cells array, size: %zu bytes).\n", 10,
                    10 * sizeof(long double));
            exit(EXIT_FAILURE);
        }

        ssize_t t = 10;
        for (ssize_t i = 0; i < 3; ++i) {
            srand(conf.seed);
            array[i] = final_BT(t, keys, max_search, max_delete, conf.max_instances);

            t *= 10;
        }

        fprintf(fp, "%zu", keys);
        for (ssize_t i = 0; i < 3; ++i) {
            fprintf(fp, ",%Lf", array[i]);
        }
        fprintf(fp, "\n");

        free(array);

        ++conf.seed;
    }

    if (fclose(fp) == EOF) fprintf(stderr, "Failed to flush buffered data on `%s`\n", file);
}
