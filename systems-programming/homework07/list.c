/* list.c: List Structure */

#include "list.h"

/* List Functions */

/**
 * Create a List structure.
 *
 * @return  Pointer to new List structure (must be deleted later).
 **/
List *	list_create() {
    List *newList = calloc(1, sizeof(List)); // Use calloc to set everything to 0

    newList->sentinel.next = &newList->sentinel;
    newList->sentinel.prev = &newList->sentinel;

    return newList;
}

/**
 * Delete List structure.
 *
 * @param   l       Pointer to List structure.
 * @param   release Whether or not to release the string values.
 **/
void	list_delete(List *l, bool release) {
    Node *current = l->sentinel.next; // Start with first node after sentinel node

    while (current != &l->sentinel) {
        Node *next = current->next;
        node_delete(current, release); // Call node_delete and pass in release variable
        current = next;
    }

    free(l);
}

/**
 * Add new Value to back of List structure.
 *
 * @param   l       Pointer to List structure.
 * @param   v       Value to add to back of List structure.
 **/
void    list_append(List *l, Value v) {
    Node *appNode = node_create(v, &l->sentinel, l->sentinel.prev);

    l->sentinel.prev->next = appNode;
    l->sentinel.prev = appNode;
    l->size++;
}

/**
 * Remove Value at specified index from List structure.
 *
 * @param   l       Pointer to List structure.
 * @param   index   Index of Value to remove from List structure.
 *
 * @return  Value at index in List structure (-1 if index is out of bounds).
 **/
Value list_pop(List *l, size_t index) {
    if (index >= l->size) {
        return (Value)-1L;
    }

    // Find the node based on index
    Node *current = l->sentinel.next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    // Unlink the node
    current->prev->next = current->next;
    current->next->prev = current->prev;

    Value v = current->value;
    node_delete(current, false);
    l->size--;

    return v;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
