#include <tap.h>
#include "../src/merc.h"
#include "db_test.c"
#include "handler_test.c"
#include "input_test.c"
#include "skills_test.c"
#include "act_obj_test.c"

int main(int argc, char **argv) {
    plan(NO_PLAN);
    
    run_db_tests();
    run_handler_tests();
    run_input_tests();
    run_skills_tests();
    run_act_obj_tests();
    
    done_testing();
}

