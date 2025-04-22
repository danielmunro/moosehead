#include <string.h>

#include "../src/db.h"

void test_str_dup_hello_world() {
    ok(strcmp("hello world", str_dup("hello world")) == 0);
}

void test_str_dup_empty() {
    ok(strcmp("", str_dup("")) == 0);
}

void run_db_tests() {
    test_str_dup_hello_world();
    test_str_dup_empty();
}
