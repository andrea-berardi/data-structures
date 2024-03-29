#include <stdio.h>
#include <stdlib.h>
#include <string.h> // required for strcmp()
#include <stdbool.h> // required to use idiomatically the boolean type

#include "headers/utils/utils.h"
#include "headers/utils/tests.h"
#include "headers/utils/colors.h"
#include "headers/utils/experiments.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments supplied.\n");
        error_menu(argv);

        exit(EXIT_FAILURE);
    }

    /* Lab. 1A configurations */
    Configuration lab1A_conf = {
            .min_keys = 0, // minimum number of keys in the tree
            .max_keys = 100000, // maximum number of keys in the tree
            .max_instances = 100, // how many times to repeat the same test
            .step = 1000, // the amount of keys will grow this much at each test
            .search_delete_ratio = 60, // ratio of insertions/deletions
            .seed = 10, // srand()'s starting seed
            .t = -1 // useless, B-Tree configuration
    };

    /* Lab. 1B configurations */
    Configuration lab1B_conf = {
            .min_keys = 0, // minimum number of keys in the tree
            .max_keys = 10000, // maximum number of keys in the tree
            .max_instances = 100, // how many times to repeat the same test
            .step = 250, // the amount of keys will grow this much at each test
            .search_delete_ratio = 60, // ratio of insertions/deletions
            .seed = 10, // srand()'s starting seed
            .t = -1 // useless, B-Tree configuration
    };

    /* Lab. 2 configurations */
    Configuration lab2_conf = {
            .min_keys = 0, // minimum number of keys in the tree
            .max_keys = 1000000, // maximum number of keys in the tree
            .max_instances = 50, // how many times to repeat the same test
            .step = 10000, // the amount of keys will grow this much at each test
            .search_delete_ratio = 60, // ratio of insertions/deletions
            .seed = 10, // srand()'s starting seed
            .t = -1, // useless, B-Tree configuration
    };

    /* Lab. 3 configurations */
    Configuration lab3_conf = {
            .min_keys = 0, // minimum number of keys in the tree
            .max_keys = 1000000, // maximum number of keys in the tree
            .max_instances = 10, // how many times to repeat the same test
            .step = 50000, // the amount of keys will grow this much at each test
            .search_delete_ratio = 60, // ratio of insertions/deletions
            .seed = 10, // srand()'s starting seed
            .t = 50 // try with 1000 to show the difference
    };

    /* Final experiment */
    Configuration final_conf = {
            .min_keys = 0, // minimum number of keys in the tree                  
            .max_keys = 1000000, // maximum number of keys in the tree
            .max_instances = 10, // how many times to repeat the same test        
            .step = 50000, // the amount of keys will grow this much at each test
            .search_delete_ratio = 60, // ratio of insertions/deletions           
            .seed = 10, // srand()'s starting seed                                
            .t = 10 // try with 1000 to show the difference
    };

    if (strcmp(argv[1], "1A") == 0) {
        /* Lab. 1A - (BSTs) Binary Search Trees */
        bold_yellow("Running Lab. 1A (Binary Search Trees)... ");
        lab_1A("../results/lab_1/1A/lab_1A.csv", lab1A_conf);
    } else if (strcmp(argv[1], "1B") == 0) {
        /* Lab. 1B - (LLs) Linked Lists, (BSTs) Binary Search Trees */
        bold_yellow("Running Lab. 1B (Linked Lists, Binary Search Trees)... ");
        lab_1B("../results/lab_1/1B/lab_1B.csv", lab1B_conf);
    } else if (strcmp(argv[1], "2") == 0) {
        /* Lab. 2 - (RBTs) Red-Black Trees, (BSTs) Binary Search Trees */
        bold_yellow("Running Lab. 2 (Red-Black Trees, Binary Search Trees)... ");
        lab_2("../results/lab_2/lab_2.csv", lab2_conf);
    } else if (strcmp(argv[1], "3") == 0) {
        /* Lab. 3 - (BTs) B-Trees, (RBTs) Red-Black Trees, (BSTs) Binary Search Trees */
        bold_yellow("Running Lab. 3 (B-Trees, Red-Black Trees, Binary Search Trees)... ");
        lab_3("../results/lab_3/lab_3.csv", lab3_conf);
    } else if (strcmp(argv[1], "4") == 0) {
        /* Final experiment */
        bold_yellow("Running Final (BTs with variable degree t)... ");
        lab_final("../results/final/final.csv", final_conf);
    } else if (strcmp(argv[1], "test") == 0) {
        /* Test the DS's integrity */
        bold_yellow("Running unit and Data Structures integrity tests... ");
        if (run_tests() == true) {
            bold_green("All tests passed!\n");

            return EXIT_SUCCESS;
        } else {
            bold_red("Some tests failed!\n");

            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid argument supplied: `%s`\n", argv[1]);
        error_menu(argv);

        exit(EXIT_FAILURE);
    }

    bold_green("Done!\n"); // if we arrive here, the experiments were successful

    /* Automatic plotter (Python script) */
    plotter(argv[1]); // the function handles potential errors

    return EXIT_SUCCESS;
}
