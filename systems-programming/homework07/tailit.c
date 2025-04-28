/* tailit.c: Output the last part of files */

#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: tailit [-n NUMBER]\n\n");
    fprintf(stderr, "    -n NUMBER  Output the last NUMBER of lines (default is 10)\n");
    exit(status);
}

List *tail_stream(FILE *stream, size_t limit) {
    List *sequence = list_create();
    char buffer[BUFSIZ];

    while (fgets(buffer, sizeof(buffer), stream) != NULL) {
        char *line = strdup(buffer);
        list_append(sequence, (Value){.string = line});

        // If over limit, remove the oldest line (head)
        if (sequence->size > limit) {
            Value old = list_pop(sequence, 0);
            free(old.string);  // Free the popped line's string
        }
    }

    return sequence;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    size_t limit = 10; // Set baseline limit

    // TODO: Parse command line arguments
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            usage(EXIT_SUCCESS);
        } else {
            usage(EXIT_FAILURE);
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "-n") == 0) {
            limit = (size_t)atoi(argv[2]);
        } else {
            usage(EXIT_FAILURE);
        }
    } else if (argc > 3) {
        usage(EXIT_FAILURE);
    }

    // TODO: Construct tail of stream
    List *lines = tail_stream(stdin, limit);

    // TODO: Print out tail
    while (lines->size > 0) {
        Value v = list_pop(lines, 0);
        printf("%s", v.string);
        free(v.string);
    }

    list_delete(lines, false);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
