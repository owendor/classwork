/* trit.c: translation utility */

#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isspace

/* Constants */

enum {
    LOWER    = 1<<1,
    UPPER    = 1<<2,
    TITLE    = 1<<3,
    STRIP    = 1<<4,
    DELETE   = 1<<5,
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: trit SET1 SET2\n\n");
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "  -l      Convert to lowercase\n");
    fprintf(stderr, "  -u      Convert to uppercase\n");
    fprintf(stderr, "  -t      Convert to titlecase\n");
    fprintf(stderr, "  -s      Strip trailing whitespace\n");
    fprintf(stderr, "  -d      Delete letters in SET1\n");
    exit(status);
}

void translate_stream(FILE *stream, const char *set1, const char *set2, int flags) {
    char line[256];

    while (fgets(line, sizeof(line), stream) != NULL) {
        // Remove newline char if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Translate or delete part of string
        char processed_line[1024];
        strcpy(processed_line, line);

        if (flags & DELETE) {
            str_delete(processed_line, set1, line);
            strcpy(processed_line, line);
            set2 = "";
        } else if (set1 != NULL && set2 != NULL) {
            str_translate(processed_line, set1, set2, line);
            strcpy(processed_line, line);
        }

        // Filters
        if (flags & LOWER) {
            str_lower(processed_line, line);
            strcpy(processed_line, line);
        }

        if (flags & UPPER) {
            str_upper(processed_line, line);
            strcpy(processed_line, line);
        }

        if (flags & TITLE) {
            str_title(processed_line, line);
            strcpy(processed_line, line);
        }

        if (flags & STRIP) {
            str_rstrip(processed_line, " \t\r\f\v", line); // all the whitespace characters I can think of (has no newline)
            strcpy(processed_line, line);
        }

        printf("%s\n", processed_line);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int flags = 0;
    char *set1 = NULL;
    char *set2 = NULL;
    int positional_args_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            flags |= LOWER;
        } else if (strcmp(argv[i], "-u") == 0) {
            flags |= UPPER;
        } else if (strcmp(argv[i], "-t") == 0) {
            flags |= TITLE;
        } else if (strcmp(argv[i], "-d") == 0) {
            flags |= DELETE;
        } else if (strcmp(argv[i], "-s") == 0) {
            flags |= STRIP;
        } else if (strcmp(argv[i], "-h") == 0) {
            usage(0);
        } else {
            positional_args_count++;
            if (positional_args_count == 1) {
                set1 = argv[i];
            } else if (positional_args_count == 2) {
                set2 = argv[i];
            } else {
                usage(1);
            }
        }
    }

    translate_stream(stdin, set1, set2, flags);

    return 0;
}
/* Main Execution */

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

