#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data_structures/linked_lists.h"

/**
 ** @file linked_lists.c
 ** @brief Linked Lists implementation
 ** @author Andrea Berardi
 ** @date 20/02/2022
 **/

/**
 ** @brief Search for a node in a linked list
 ** @param L the linked list to search in
 ** @param key the key to search for
 ** @return node containing the key
 **/
LLNode *LLSearch(LLHead *L, int k) {
    LLNode *x = L->head;

    while (x != NULL && x->key != k) {
        x = x->next;
    }

    return x;
}

/**
 ** @brief Create a new node
 ** @param k the key to store in the node
 ** @return node containing the key
 **/
LLNode *LLNewNode(int k) {
    LLNode *x = malloc(sizeof(LLNode));

    x->previous = NULL;
    x->next = NULL;
    x->key = k;

    return x;
}

/**
 ** @brief Insert a node in a linked list
 ** @param L the linked list to insert in
 ** @param x the node to insert
 **/
void LLInsert(LLHead *L, LLNode *x) {
    x->next = L->head;

    if (L->head != NULL)
        L->head->previous = x;

    L->head = x;
    x->previous = NULL;

    L->cardinality += 1;
}

/**
 ** @brief Insert a key in a linked list
 ** @param L the linked list to insert in
 ** @param k the key to insert
 **/
void LLInsertKey(LLHead *L, int k) {
    LLNode *x = LLNewNode(k);

    LLInsert(L, x);
}

/**
 ** @brief Remove a node from a linked list
 ** @param L the linked list to remove from
 ** @param x the node to remove
 **/
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

/**
 ** @brief Remove a key from a linked list
 ** @param L the linked list to delete from
 ** @param k the key to delete
 **/
void LLDeleteKey(LLHead *L, int k) {
    LLNode *x = LLSearch(L, k);

    if (x != NULL) LLDelete(L, x);
}

/**
 ** @brief Create a new linked list
 ** @param x the head of the linked list (can be NULL)
 ** @return address of the linked list's head
 **/
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

/**
 ** @brief Destroy a linked list
 ** @param L the linked list to destroy
 **/
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
