/* filter.c: Filter functions */

#include "findit.h"

#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Filter Functions */

/**
 * Determines if file at specified path has matching file type.
 * @param   path        Path string
 * @param   options     Pointer to options structure
 * @return  true if file at specified path has matching file type specified in
 * options.
 **/
bool	filter_by_type(const char *path, Options *options) {
    // TODO: Use lstat
    struct stat statbuf;

    // If lstat fails (returns non-zero), return false
    if (lstat(path, &statbuf) != 0) {
        return false;
    }

    // Extract file type from mode using statbuf and bitmask
    mode_t file_type = statbuf.st_mode & S_IFMT;

    // Compare with the specified type
    bool is_match = (file_type == options->type);

    return is_match; // Return true if it's the same
}

/**
 * Determines if file at specified path has matching basename.
 * @param   path        Path string
 * @param   options     Pointer to options structure
 * @return  true if file at specified path has basename that matches specified
 * pattern in options.
 **/
bool	filter_by_name(const char *path, Options *options) {
    // TODO: Use basename and fnmatch
    char *path_copy = strdup(path); // Create copy for basename

    // Get basename and check if pattern matches
    char *base = basename(path_copy);
    bool match = (fnmatch(options->name, base, 0) == 0);

    free(path_copy);

    return match;
}

/**
 * Determines if file at specified path has matching access mode.
 * @param   path        Path string
 * @param   options     Pointer to options structure
 * @return  true if file at specified path has matching access mode specified
 * in options.
 **/
bool	filter_by_mode(const char *path, Options *options) {
    // TODO: Use access
    bool has_access = (access(path, options->mode) == 0); // Check access w/ process's user ID

    return has_access;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
