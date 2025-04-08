#include <stdio.h>
#include "log.h"

/*
 * Writes a string to stdout if LOG_LEVEL is set to the highest level, LOG_DEBUG.
 */
void log_debug(const char *str) {
    if (LOG_LEVEL >= LOG_DEBUG) {
        printf("[debug] %s\n", str);
    }
}

/*
 * Writes a string to stdout if LOG_LEVEL is set to at least LOG_INFO.
 */
void log_info(const char *str) {
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
