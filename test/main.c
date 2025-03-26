#include <tap.h>
#include "../src/merc.h"
#include "handler_test.c"
#include "input_test.c"
#include "skills_test.c"

int main(int argc, char **argv) {
    run_handler_tests();
    run_input_tests();
    run_skills_tests();
}
