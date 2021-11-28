// Header guards:
// patterns of preprocessor directives that protect a header from being included multiple times
#ifndef TREES_LINKED_LISTS_H
#define TREES_LINKED_LISTS_H

typedef struct ll_node {
    int key;
    struct ll_node* previous;
    struct ll_node* next;
} LLNode;

typedef struct ll_head {
    size_t cardinality; // amount of elements in the linked list
    struct ll_node* head;
} LL;

LLNode *LLListSearch(LL *L, int k);

void LLListInsertKey(LL *L, int k);

void LLListDeleteKey(LL *L, int k);

LL *LLNewList(LLNode *x);

#endif //TREES_LINKED_LISTS_H

// #pragma once
// an alternative to header guards
