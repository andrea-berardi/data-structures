#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../headers/linked_lists/linked_lists.h"

LLNode *LLListSearch(LL *L, int k) {
    LLNode *x = L->head;

    while (x != NULL && x->key != k) {
        x = x->next;
    }

    return x;
}

LLNode *LLNewNode(int k) {
    LLNode *x = malloc(sizeof(LLNode));

    x->previous = NULL;
    x->next = NULL;
    x->key = k;
}

void LLListInsert(LL *L, LLNode *x) {
    x->next = L->head;

    if (L->head != NULL)
        L->head->previous = x;

    L->head = x;
    x->previous = NULL;

    L->cardinality += 1;
}

void LLListInsertKey(LL *L, int k) {
    LLNode *x = LLNewNode(k);

    LLListInsert(L, x);
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

    free(x);
    x = NULL;
}

void LLListDeleteKey(LL *L, int k) {
    LLNode *x = LLListSearch(L, k);

    LLListDelete(L, x);
}

LL *LLNewList(LLNode *x) {
    LL *L = malloc(sizeof(LL));

    L->cardinality = 0;

    if (x != NULL) {
        L->head = x;
    } else {
        L->head = NULL;
    }

    return L;
}
