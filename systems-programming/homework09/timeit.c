/* timeit.c: Run command with a time limit */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0
#define debug(M, ...) \
    if (Verbose) { \
        fprintf(stderr, "%s:%d:%s: " M, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    }

#define BILLION 1000000000.0

/* Globals */

int  Timeout  = 10;
bool Verbose  = false;
int  ChildPid = 0;

/* Functions */

/**
 * Display usage message and exit.
 * @param   status      Exit status.
 **/
void	usage(int status) {
    fprintf(stderr, "Usage: timeit [options] command...\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -t SECONDS  Timeout duration before killing command (default is %d)\n", Timeout);
    fprintf(stderr, "    -v          Display verbose debugging output\n");
    exit(status);
}

/**
 * Parse command line options.
 * @param   argc        Number of command line arguments.
 * @param   argv        Array of command line argument strings.
 * @return  Array of strings representing command to execute (must be freed).
 **/
char ** parse_options(int argc, char **argv) {
    // TODO: Iterate through command line arguments to determine Timeout and
    // Verbose flags

    if (argc == 1) usage(EXIT_FAILURE); // Exit if no arguments provided

    int arg_index = 1; // Start with the first argument after the program call

    if (streq(argv[1], "-h")) { // Check for the help flag
        usage(EXIT_SUCCESS);
    } else {
        while (arg_index < argc) {
            if (streq(argv[arg_index], "-t")) {
                if (arg_index + 1 < argc) {
                    Timeout = atoi(argv[arg_index + 1]);
                    arg_index += 2;
                } else usage(EXIT_FAILURE);
            } else if (streq(argv[arg_index], "-v")) {
                Verbose = true;
                arg_index++;
            } else break;
        }
    }

    debug("Timeout = %d\n", Timeout);
    debug("Verbose = %d\n", Verbose);

    // TODO: Copy remaining arguments into new array of strings
    int command_count = argc - arg_index;
    char **command = NULL;
    if (command_count > 0) {
        command = malloc((command_count + 1) * sizeof(char *));
        memcpy(command, &argv[arg_index], command_count * sizeof(char *)); // AI Code review updated
        command[command_count] = NULL;
    } else usage(EXIT_FAILURE);

    if (Verbose) {
        // TODO: Print out new array of strings (to stderr)
        debug("Command =");
        for (int i = 0; command[i]; i++) {
            debug(" %s", command[i]);
        }
        debug("\n");
    }

    return command;
}

/**
* Handle signal.
* @param   signum      Signal number.
**/
void    handle_signal(int signum) {
    // TODO: Kill child process gracefully, then forcefully
    debug("Killing child %d...\n", ChildPid);

    // First try to terminate gradefully and wait
    kill(ChildPid, SIGTERM);
    usleep(100000); // 0.1 sec

    // If child still exists, force kill
    if (kill(ChildPid, 0) == 0) {
        kill(ChildPid, SIGKILL);
    }
}

/* Main Execution */

int	main(int argc, char *argv[]) {
    // TODO: Parse command line options
    char **command = parse_options(argc, argv);

    // TODO: Register alarm handler and save start time
    debug("Registering handlers...\n");
    signal(SIGALRM, handle_signal);

    debug("Grabbing start time...\n");
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // TODO: Fork child process:
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        free(command);
        return EXIT_FAILURE;
    }

    //  1. Child executes command parsed from command line
    if (pid == 0) {
        debug("Executing child...\n");
        execvp(command[0], command);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    //  2. Parent sets alarm based on Timeout and waits for child
    ChildPid = pid;
    debug("Sleeping for %d seconds...\n", Timeout);
    alarm(Timeout);

    int status;
    debug("Waiting for child %d...\n", ChildPid);
    if (waitpid(ChildPid, &status, 0) < 0) {
        perror("waitpid");
        free(command);
        return EXIT_FAILURE;
    }

    // TODO: Print out child's exit status or termination signal
    if (WIFEXITED(status)) {
        debug("Child exit status: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        debug("Child killed by signal: %d\n", WTERMSIG(status));
    }

    // TODO: Print elapsed time
    debug("Grabbing end time...\n");
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / BILLION;
    printf("Time Elapsed: %0.1lf\n", elapsed);

    // TODO: Cleanup
    free(command);

    status = WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status);

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
