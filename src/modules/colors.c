#include <stdio.h>

#include "../headers/colors.h"

void red(char *str) {
    printf("\033[0;31m%s\033[0m", str);
    fflush(stdout);
}

void bold_red(char *str) {
    printf("\033[1;31m%s\033[0m", str);
    fflush(stdout);
}

void yellow(char *str) {
    printf("\033[0;33m%s\033[0m", str);
    fflush(stdout);
}

void bold_yellow(char *str) {
    printf("\033[1;33m%s\033[0m", str);
    fflush(stdout);
}

void green(char *str) {
    printf("\033[0;32m%s\033[0m", str);
    fflush(stdout);
}

void bold_green(char *str) {
    printf("\033[1;32m%s\033[0m", str);
    fflush(stdout);
}

void blue(char *str) {
    printf("\033[0;34m%s\033[0m", str);
    fflush(stdout);
}

void bold_blue(char *str) {
    printf("\033[1;34m%s\033[0m", str);
    fflush(stdout);
}
