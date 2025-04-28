/* curlit.c: Simple HTTP client*/

#include "socket.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <netdb.h>

/* Constants */

#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'
#define BILLION         (1000000000.0)
#define MEGABYTES       (1<<20)

/* Macros */

#define streq(a, b) (strcmp(a, b) == 0)

/* Structures */

typedef struct {
    char host[NI_MAXHOST];
    char port[NI_MAXSERV];
    char path[PATH_MAX];
} URL;

/* Functions */

/**
 * Display usage message and exit.
 * @param   status      Exit status.
 **/
void    usage(int status) {
    fprintf(stderr, "Usage: curlit [-h] URL\n");
    exit(status);
}

/**
 * Parse URL string into URL structure.
 * @param   s       URL string
 * @param   url     Pointer to URL structure
 **/
void    parse_url(const char *s, URL *url) {
    // TODO: Copy data to local buffer
    char buffer[PATH_MAX];
    strncpy(buffer, s, PATH_MAX);
    buffer[PATH_MAX - 1] = '\0';  // This makes sure the string is null-terminated

    // TODO: Skip scheme to host
    char *host_start = strstr(buffer, HOST_DELIMITER);
    if (host_start) {
        host_start += strlen(HOST_DELIMITER);
    } else {
        host_start = buffer;
    }

    // TODO: Split host:port from path
    char *path_start = strchr(host_start, PATH_DELIMITER);
    if (path_start) {
        strncpy(url->path, path_start, PATH_MAX);
        url->path[PATH_MAX - 1] = '\0';
        *path_start = '\0';
    } else {
        strcpy(url->path, "/"); // if no path found, use root
    }

    // TODO: Split host and port
    char *port = strchr(host_start, PORT_DELIMITER);
    if (!port) {
        strcpy(url->port, "80"); // the default port
    } else {
        *port = '\0'; // had to modify from the suggested code due to an error with types
        port++;
        strncpy(url->port, port, NI_MAXSERV);
        url->port[NI_MAXSERV - 1] = '\0';
    }

    // TODO: Copy components to URL
    strncpy(url->host, host_start, NI_MAXHOST);
    url->host[NI_MAXHOST - 1] = '\0';
}

/**
 * Fetch contents of URL and print to standard out.
 *
 * Print elapsed time and bandwidth to standard error.
 * @param   s       URL string
 * @param   url     Pointer to URL structure
 * @return  true if client is able to read all of the content (or if the
 * content length is unset), otherwise false
 **/
bool    fetch_url(URL *url) {
    // TODO: Grab start time
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // TODO: Connect to remote host and port
    FILE *client_socket = socket_dial(url->host, url->port);
    if (!client_socket) {
        fprintf(stderr, "Failed to connect to %s:%s\n", url->host, url->port);
        return false;
    }

    // TODO: Send request to server
    fprintf(client_socket, "GET %s HTTP/1.0\r\n", url->path);
    fprintf(client_socket, "Host: %s\r\n", url->host);
    fprintf(client_socket, "\r\n");
    fflush(client_socket);

    // TODO: Read status response from server
    char buffer[BUFSIZ];
    if (!fgets(buffer, BUFSIZ, client_socket)) {
        fprintf(stderr, "Failed to read server status response\n");
        fclose(client_socket);
        return false;
    }

    bool is_status_ok = (strstr(buffer, "200 OK") != NULL); // set flag that checks for 200 OK status

    // TODO: Read response headers from server
    size_t content_length = 0;
    while (fgets(buffer, BUFSIZ, client_socket) && buffer[0] != '\r' && buffer[0] != '\n') {
        sscanf(buffer, "Content-Length: %lu", &content_length);
    }

    // TODO: Read response body from server
    size_t bytes_read = 0;
    size_t total_bytes = 0;

    while ((bytes_read = fread(buffer, 1, BUFSIZ, client_socket)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, stdout);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Failed to write all data to stdout\n");
            fclose(client_socket);
            return false;
        }
        total_bytes += bytes_read;
    }

    // TODO: Grab end time
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / BILLION;

    // TODO: Output metrics
    fprintf(stderr, "Time Elapsed: %.2f s\n", elapsed);
    fprintf(stderr, "Bandwidth:    %.2f MB/s\n", (total_bytes / elapsed) / MEGABYTES);

    fclose(client_socket);

    // Return true if status is ok and either the expected content length was 0
    // or we received at least as much content as was expected
    return is_status_ok && (content_length == 0 || total_bytes >= content_length);
}

/* Main Execution */

int     main(int argc, char *argv[]) {
    // TODO: Parse command line options
    if (argc != 2) {
        usage(EXIT_FAILURE);
    } else if (streq(argv[1], "-h")) {
        usage(EXIT_SUCCESS);
    } else if (argv[1][0] == '-') {
        usage(EXIT_FAILURE);
    }

    // TODO: Parse URL
    URL url = {0};
    parse_url(argv[1], &url);

    // TODO: Fetch URL
    if (fetch_url(&url)) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
