// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef DS_LINKED_LISTS_H
#define DS_LINKED_LISTS_H

#include <stdlib.h>

/**
 ** @file linked_lists.h
 ** @brief Linked Lists implementation (header)
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Structure of a node of a Linked List
 **/
typedef struct ll_node {
    int key;
    struct ll_node *previous;
    struct ll_node *next;
} LLNode;

/**
 ** @brief Structure of a Linked List
 **/
typedef struct ll_head {
    size_t cardinality; // amount of elements in the linked list
    struct ll_node *head;
} LLHead;

LLNode *LLSearch(LLHead *L, int k);

void LLInsertKey(LLHead *L, int k);

void LLDeleteKey(LLHead *L, int k);

LLHead *LLNewList(LLNode *x);

void LLDestroyList(LLHead *L);

#endif //DS_LINKED_LISTS_H

// #pragma once
// an alternative to header guards
