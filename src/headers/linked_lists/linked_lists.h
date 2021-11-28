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
    size_t cardinality; // practical usage: it'll define the dimension of the arrays we'll use for "TreeWalks"
    struct ll_node* head;
} LL;

LLNode *LLListSearch(LL *L, int k);

void LLListInsert(LL *L, LLNode *x);

void LLListDelete(LL *L, LLNode *x);

#endif //TREES_LINKED_LISTS_H

// #pragma once
// an alternative to header guards
