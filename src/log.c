#include <stdio.h>
#include "log.h"

void log_debug(const char *str) {
    if (LOG_LEVEL >= LOG_DEBUG) {
        printf("[debug] %s\n", str);
    }
}

/*
 * Writes a string to stdout.  No specific log level.
 */
void log_string(const char *str) {
    if (LOG_LEVEL >= LOG_INFO) {
        printf("[info ] %s\n", str);
    }
}

/*
 * Writes a string to stderr.
 */
void log_error(const char *str) {
    fprintf(stderr, "[error] %s\n", str);
}
