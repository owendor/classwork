/* str.c: string library */

#include "str.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

/**
 * Convert string to lowercase.
 * @param   s	    String to convert
 * @param   w	    Pointer to buffer that holds result of conversion
 **/
 void str_lower(const char *s, char *w) {
     while (*s) {
         *w = tolower(*s);
         s++;
         w++;
     }
     *w = '\0';
 }

/**
 * Convert string to uppercase.
 * @param   s	    String to convert
 * @param   w	    Pointer to buffer that holds result of conversion
 **/
void str_upper(const char *s, char *w) {
    while (*s) {
        *w = toupper(*s);
        s++;
        w++;
    }
    *w = '\0';
}

/**
 * Convert string to titlecase.
 * @param   s	    String to convert
 * @param   w	    Pointer to buffer that holds result of conversion
 **/
void str_title(const char *s, char *w) {
    if (*s) {
        *w = toupper(*s);
        w++;
        s++;
        while (*s) {
            if (!isalpha(*(s - 1))) {
                *w = toupper(*s);
            } else {
                *w = tolower(*s);
            }
            s++;
            w++;
        }
    }
    *w = '\0';
}

void str_rstrip(const char *s, const char *chars, char *w) {
    // Safety checks
    if (!s || !w) return;

    bool strip_chars[256] = {0};
    const unsigned char *p = (const unsigned char *)s;
    size_t length = 0;

    // Build lookup table
    if (!chars) {
        // Strip standard whitespace
        strip_chars[' ']  = true;
        strip_chars['\t'] = true;
        strip_chars['\n'] = true;
    } else {
        for (; *chars; chars++)
            strip_chars[(unsigned char)*chars] = true;
    }

    // Find string length and last non-stripped character
    while (*p) p++;
    while (p > (const unsigned char *)s && strip_chars[*(p-1)])
        p--;

    // Calculate length and copy
    length = p - (const unsigned char *)s;
    memcpy(w, s, length);
    w[length] = '\0';
}

/**
 * Delete characters from string.
 * @param   s	    String to delete from
 * @param   chars   Characters to delete
 * @param   w	    Pointer to buffer that holds result of deletion
 **/
void str_delete(const char *s, const char *chars, char *w) {
    bool del_chars[256] = {0};

    // Create lookup table
    while (*chars) {
        del_chars[(unsigned char)*chars] = true;
        chars++;
    }

    // Copy non-deleted chars to w
    while (*s) {
        if (!del_chars[(unsigned char)*s]) {
            *w = *s;
            w++;
        }
        s++;
    }
    *w = '\0';
}

/**
 * Translate characters in 'from' with corresponding characters in 'to'.
 * @param   s       String to translate
 * @param   from    String with characters to translate
 * @param   to      String with corresponding translation characters
 * @param   w	    Pointer to buffer that holds result of translation
 **/
void str_translate(const char *s, const char *from, const char *to, char *w) {
    unsigned char translate_table[256];
    int i;

    for (i = 0; i < 256; i++) {
        translate_table[i] = i;
    }

    // Create the translation map
    while (*from && *to) {
        translate_table[(unsigned char)*from] = *to;
        from++;
        to++;
    }

    // Translate
    while (*s) {
        *w = translate_table[(unsigned char)*s];
        s++;
        w++;
    }
    *w = '\0';
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
