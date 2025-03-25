#include <stdio.h>

/*
 * Writes a string to stdout.  No specific log level.
 */
void log_string(const char *str) {
    printf("%s\n", str);
}

/*
 * Writes a string to stderr.
 */
void log_error(const char *str) {
    fprintf(stderr, "%s\n", str);
}
