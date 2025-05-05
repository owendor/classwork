/* findit.c: Search for files in a directory hierarchy */

#include "findit.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)

/* Functions */

/**
 * Print usage message and exit with status
 * @param   status      Exit status
 **/
void usage(int status) {
    fprintf(stderr, "Usage: findit PATH [OPTIONS]\n\n");
    fprintf(stderr, "Options:\n\n");
    fprintf(stderr, "   -type [f|d]	File is of type f for regular file or d for directory\n");
    fprintf(stderr, "   -name pattern	Name of file matches shell pattern\n");
    fprintf(stderr, "   -executable	File is executable or directory is searchable by user\n");
    fprintf(stderr, "   -readable	File is readable by user\n");
    fprintf(stderr, "   -writable	File is writable by user\n");
    exit(status);
}

/**
 * Recursively walk specified directory, adding all file system entities to
 * specified files list.
 * @param   root        Directory to walk
 * @param   files       List of files found
 **/
void    find_files(const char *root, List *files) {
    // Only add the root if it's the first call by testing if the list head is empty
    if (files->head == NULL) {
        char *root_copy = strdup(root);
        if (root_copy) {
            list_append(files, (Data){.string = root_copy});
        }
    }

    // Open directory
    DIR *dir = opendir(root);
    if (dir == NULL) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip current/parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        char path[BUFSIZ];
        snprintf(path, sizeof(path), "%s/%s", root, entry->d_name);

        // Add the path to the list
        char *path_copy = strdup(path);
        if (path_copy) {
            list_append(files, (Data){.string = path_copy});
        }

        // Check if it's a directory for recursion
        struct stat s;
        if (lstat(path, &s) == 0 && S_ISDIR(s.st_mode)) {
            find_files(path, files); // The recursive call
        }
    }

    closedir(dir);
}

/**
 * Iteratively filter list of files with each filter in list of filters.
 * @param   files       List of files
 * @param   filters     List of filters
 * @param   options     Pointer to options structure
 **/
void	filter_files(List *files, List *filters, Options *options) {
    // Apply each filter in sequence to files list
    for (Node *filter_node = filters->head; filter_node; filter_node = filter_node->next) {
        Filter filter = filter_node->data.function;

        // Apply the filter to files list
        list_filter(files, filter, options, true);
    }
}

void easterEgg() {
    printf(
        "\n**Ode to the Crimson Text**\n"
        "*A shell user's lament*\n\n"

        "The cursor blinked, a patient foe,\n"
        "I typed with zeal: `rm -rf /oops/no`\n"
        "The shell screamed back in scarlet hue—\n"
        "*\"Unmatched quote! Syntax taboo!\"*\n\n"

        "A pipe went rogue, `grep ^[a-z] > file`,\n"
        "The gods of bash let loose their guile:\n"
        "*\"Ambiguous redirect!\"* they decreed,\n"
        "As my homework dissolved to digital greed.\n\n"

        "I summoned roots with `sudo !-1`,\n"
        "(That last command had *almost* won)—\n"
        "*\"Permission denied\"* the kernel spat,\n"
        "My hopes lay dashed, my ego flat.\n\n"

        "The regex beast, that cryptic art,\n"
        "`sed 's/([0-9]+/1/'` tore me apart—\n"
        "*\"Unterminated s-command\"* it swore,\n"
        "My edits fled through Death's dark door.\n\n"

        "Yet in this dance of shame and woe,\n"
        "Where `chmod 755 ~/bin/ohno`\n"
        "Brings *\"Cannot access\"* purgatory—\n"
        "We learn the shell's grim allegory:\n\n"

        "Each failed command, each syntax crime,\n"
        "Is but a step to mastery's climb.\n"
        "(Though `man` pages still read like lies\n"
        "And tab-complete mocks tear-filled eyes.)\n\n"

        "The terminal giveth, the terminal taketh—\n"
        "Blessed are those whose PATH it maketh.\n"
        "For all who type with trembling hands:\n"
        "*Press up-arrow to try again.*\n\n"
    );
}

/* Main Execution */

int main(int argc, char *argv[]) {
    // Check minimum arguments
    if (argc < 2) {
        usage(EXIT_FAILURE);
    }

    // Initialize data structures
    char *root = argv[1];
    Options options = {0};
    List files = {NULL, NULL};
    List filters = {NULL, NULL};

    // Parse command line arguments
    for (int i = 2; i < argc; i++) {
        const char *arg = argv[i];

        if (streq(arg, "-type")) {
            if (++i >= argc) usage(EXIT_FAILURE);

            // Get file type
            char type = argv[i][0];
            switch (type) {
                case 'f': options.type = S_IFREG; break;
                case 'd': options.type = S_IFDIR; break;
                default:  usage(EXIT_FAILURE);
            }
            list_append(&filters, (Data){.function = filter_by_type});
        } else if (streq(arg, "-name")) {
            if (++i >= argc) usage(EXIT_FAILURE);
            options.name = argv[i];
            list_append(&filters, (Data){.function = filter_by_name});
        } else if (streq(arg, "-executable")) {
            options.mode |= X_OK;
        } else if (streq(arg, "-readable")) {
            options.mode |= R_OK;
        } else if (streq(arg, "-writable")) {
            options.mode |= W_OK;
        } else {
            if (argc == 7) easterEgg();
            usage(EXIT_FAILURE); // Invalid argument
        }
    }

    // Add mode filter if any mode flags were set
    if (options.mode) {
        list_append(&filters, (Data){.function = filter_by_mode});
    }

    // Find files, filter files, print files
    find_files(root, &files);
    filter_files(&files, &filters, &options);
    list_output(&files, stdout);

    // Cleanup
    node_delete(files.head, true, true);
    node_delete(filters.head, false, true);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
