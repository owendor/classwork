/* list.c: Singly Linked List */

#include "findit.h"

#include <stdlib.h>

/* Node Functions */

/**
 * Allocate a new Node structure.
 * @param   data        Data value
 * @param   next        Pointer to next Node structure
 * @return  Pointer to new Node structure (must be deleted).
 **/
Node *  node_create(Data data, Node *next) {
    Node *n = calloc(1, sizeof(Node));

    n->data = data;
    n->next = next;

    return n;
}

/**
 * Deallocate Node structure.
 * @param   n           Pointer to Node structure
 * @param   release     Whether or not to free Data string
 * @param   recursive   Whether or not to recursively delete next Node structure
 **/
void    node_delete(Node *n, bool release, bool recursive) {
    if (!n) return; // Return if pointer is null

    // Recursively delete node structure if recursive = true
    if (recursive && n->next) {
        node_delete(n->next, release, recursive);
    }

    if (release && n->data.string) {
        free(n->data.string);
    }

    free(n);
}

/* List Functions */

/**
 * Append data to end of specified List.
 * @param   l           Pointer to List structure
 * @param   data        Data value to append
 **/
void    list_append(List *l, Data data) {
    Node *new_node = node_create(data, NULL);

    if (!l->head) {
        // Append to empty list
        l->head = new_node;
        l->tail = new_node;
    } else {
        // Append to the tail of non-empty list
        l->tail->next = new_node;
        l->tail = new_node;
    }
}

/**
 * Filter list by applying the filter function to each Data string in List with
 * the given options:
 *
 *  - If filter function returns true, then keep current Node.
 *  - Otherwise, remove current Node from List and delete it.
 *
 * @param   l           Pointer to List structure
 * @param   filter      Filter function to apply to each Data string
 * @param   options     Pointer to Options structure to use with filter function
 * @param   release     Whether or not to release data string when deleting Node
 **/
void    list_filter(List *l, Filter filter, Options *options, bool release) {
    Node *curr = l->head;
    Node *prev = NULL;

    while (curr) {
        if (filter(curr->data.string, options)) {
            // Keep this node
            prev = curr;
            curr = curr->next;
        } else {
            // Remove this node
            Node *to_delete = curr;
            curr = curr->next;

            // Update head or prev->next
            if (prev) {
                prev->next = curr;
            } else {
                l->head = curr;
            }

            // Update tail if necessary
            if (to_delete == l->tail) {
                l->tail = prev;
            }

            // Delete node
            node_delete(to_delete, release, false);
        }
    }
}

/**
 * Output each Data string in List to specified stream.
 * @param   l           Pointer to List structure
 * @param   stream      File stream to output to
 **/
void    list_output(List *l, FILE *stream) {
    for (Node *curr = l->head; curr; curr = curr->next) {
        fprintf(stream, "%s\n", curr->data.string); // Print the data string of the current node followed by a newline
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
