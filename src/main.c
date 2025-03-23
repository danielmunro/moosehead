#include <stdlib.h>
#include <stdio.h>
#include "merc.h"

int main( int argc, char **argv ) {
    int port;

    if (argc > 1) {
        if (!is_number(argv[1])) {
            char log_buf[MAX_STRING_LENGTH];
            sprintf(log_buf, "Usage: %s [port #]\n", argv[0]);
            log_error(log_buf);
            exit(1);
        }
        port = atoi(argv[1]);
    }

    return run(port);
}
