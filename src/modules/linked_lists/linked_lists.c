#include <stdio.h>
#include <stdbool.h>

#include "../../headers/linked_lists/linked_lists.h"

LLNode *LLListSearch(LL *L, int k) {
    LLNode *x = L->head;

    while (x != NULL && x->key != k) {
        x = x->next;
    }

    return x;
}

void LLListInsert(LL *L, LLNode *x) {
    x->next = L->head;

    if (L->head != NULL)
        L->head->previous = x;

    L->head = x;
    x->previous = NULL;

    L->cardinality += 1;
}

void LLListDelete(LL *L, LLNode *x) {
    if (x->previous != NULL) {
        x->previous->next = x->next;
    } else {
        L->head = x->next;
    }

    if (x->next != NULL) {
        x->next->previous = x->previous;
    }

    L->cardinality -= 1;
}
