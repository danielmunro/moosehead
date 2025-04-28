#include <string.h>

#include "../src/db.h"

void test_str_dup_hello_world() {
    ok(strcmp("hello world", str_dup("hello world")) == 0, "str_dup returns an identical string");
}

void test_str_dup_empty() {
    ok(strcmp("", str_dup("")) == 0, "str_dup works with empty strings");
}

void run_db_tests() {
    diag("Running db test");

    test_str_dup_hello_world();
    test_str_dup_empty();

    diag("Finished db test");
}
