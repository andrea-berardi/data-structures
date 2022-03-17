#include <stdio.h>

#include "../../headers/utils/colors.h"

/**
 ** @file colors.c
 ** @brief Colors for the terminal
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Print a string in red
 ** @param str the string to print
 **/
void red(char *str) {
    printf("\033[0;31m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in bold red
 ** @param str the string to print
 **/
void bold_red(char *str) {
    printf("\033[1;31m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in yellow
 ** @param str the string to print
 **/
void yellow(char *str) {
    printf("\033[0;33m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in bold yellow
 ** @param str the string to print
 **/
void bold_yellow(char *str) {
    printf("\033[1;33m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in green
 ** @param str the string to print
 **/
void green(char *str) {
    printf("\033[0;32m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in bold green
 ** @param str the string to print
 **/
void bold_green(char *str) {
    printf("\033[1;32m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in blue
 ** @param str the string to print
 **/
void blue(char *str) {
    printf("\033[0;34m%s\033[0m", str);
    fflush(stdout);
}

/**
 ** @brief Print a string in bold blue
 ** @param str the string to print
 **/
void bold_blue(char *str) {
    printf("\033[1;34m%s\033[0m", str);
    fflush(stdout);
}
