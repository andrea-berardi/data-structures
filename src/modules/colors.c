#include <stdio.h>

#include "../headers/colors.h"

void red(void) {
    printf("\033[0;31m");
}

void bold_red(void) {
    printf("\033[1;31m");
}

void yellow(void) {
        printf("\033[0;33m");
}

void bold_yellow(void) {
    printf("\033[1;33m");
}

void green(void) {
    printf("\033[0;32m");
}

void bold_green(void) {
    printf("\033[1;32m");
}

void blue(void) {
    printf("\033[0;34m");
}

void bold_blue(void) {
    printf("\033[1;34m");
}

void reset_color(void) {
    printf("\033[0m");
}
