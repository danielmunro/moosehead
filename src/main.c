#include <stdlib.h>
#include <stdio.h>

#include "merc.h"
#include "log.h"
#include "comm.h"
#include "input.h"

int main( int argc, char **argv ) {
    if (argc != 4 || !is_number(argv[2]) || !is_number(argv[3])) {
        sprintf(log_buf, "Usage: %s [build version] [mud port #] [http port #]\n", argv[0]);
        log_error(log_buf);
        exit(1);
    }

    build_version = argv[1];

    return run(atoi(argv[2]), atoi(argv[3]));
}
