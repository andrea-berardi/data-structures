#include <stdio.h>
#include <stdlib.h>

#include "../../headers/linked_lists.h"

LLNode *LLListSearch(LLHead *L, int k) {
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

    return x;
}

void LLListInsert(LLHead *L, LLNode *x) {
    x->next = L->head;

    if (L->head != NULL)
        L->head->previous = x;

    L->head = x;
    x->previous = NULL;

    L->cardinality += 1;
}

void LLListInsertKey(LLHead *L, int k) {
    LLNode *x = LLNewNode(k);

    LLListInsert(L, x);
}

void LLListDelete(LLHead *L, LLNode *x) {
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

void LLListDeleteKey(LLHead *L, int k) {
    LLNode *x = LLListSearch(L, k);

    LLListDelete(L, x);
}

LLHead *LLNewList(LLNode *x) {
    LLHead *L = malloc(sizeof(LLHead));

    L->cardinality = 0;

    if (x != NULL) {
        L->head = x;
    } else {
        L->head = NULL;
    }

    return L;
}

void LLListDestroyList(LLHead *L) {
    LLNode *x = L->head;

    while (x != NULL) {
        LLListDelete(L, x);

        x = x->next;
    }

    free(L);
    L = NULL;
}
