#include <stdlib.h>
#include <stdio.h>

#include "merc.h"
#include "log.h"
#include "comm.h"
#include "input.h"

int main( int argc, char **argv ) {
    if (argc != 3 || !is_number(argv[2])) {
        sprintf(log_buf, "Usage: %s [build version] [port #]\n", argv[0]);
        log_error(log_buf);
        exit(1);
    }

    return run(argv[1], atoi(argv[2]));
}
