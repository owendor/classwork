/* seqit.c: Print a sequence of numbers */

#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: seqit LAST\n");
    fprintf(stderr, "       seqit FIRST LAST\n");
    fprintf(stderr, "       seqit FIRST INCREMENT LAST\n");
    exit(status);
}

List *generate_sequence(ssize_t first, ssize_t increment, ssize_t last) {
    List* sequence = list_create();

    ssize_t current = first;
    if (increment > 0) {
        while (current <= last) {
            list_append(sequence, (Value){.number = current});
            current += increment;
        }
    } else {
        while (current >= last) {
            list_append(sequence, (Value){.number = current});
            current += increment;
        }
    }

    return sequence;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    // TODO: Parse command line arguments
    ssize_t first = 1, increment = 1, last = 1; // Set initial values

    switch (argc) {
        case 2:
            last = atoll(argv[1]);
            break;
        case 3:
            first = atoll(argv[1]);
            last = atoll(argv[2]);
            break;
        case 4:
            first = atoll(argv[1]);
            increment = atoll(argv[2]);
            last = atoll(argv[3]);
            break;
        default:
            usage(EXIT_FAILURE);
    }

    // TODO: Generate sequence
    List *sequence = generate_sequence(first, increment, last);

    // TODO: Print out sequence
    while (sequence->size > 0) {
        Value v = list_pop(sequence, 0);
        printf("%ld\n", v.number);
    }

    // Delete the list
    list_delete(sequence, false);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
