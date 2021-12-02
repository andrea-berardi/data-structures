#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data_structures/linked_lists.h"

LLNode *LLSearch(LLHead *L, int k) {
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

void LLInsert(LLHead *L, LLNode *x) {
    x->next = L->head;

    if (L->head != NULL)
        L->head->previous = x;

    L->head = x;
    x->previous = NULL;

    L->cardinality += 1;
}

void LLInsertKey(LLHead *L, int k) {
    LLNode *x = LLNewNode(k);

    LLInsert(L, x);
}

void LLDelete(LLHead *L, LLNode *x) {
    if (x == NULL) return; // to ensure that the node supplied is not NULL

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

void LLDeleteKey(LLHead *L, int k) {
    LLNode *x = LLSearch(L, k);

    if (x != NULL) LLDelete(L, x);
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

void LLDestroyList(LLHead *L) {
    LLNode *x = L->head;

    while (x != NULL) {
        LLNode *tmp = x->next; // temporary variable to store the address of the next node

        LLDelete(L, x);

        x = tmp;
    }

    free(L);
    L = NULL;
}
