#include <string.h>

#include "../src/input.h"

void test_is_number_positive() {
    ok(is_number("0"));
    ok(is_number("1"));
    ok(is_number("1234"));
    ok(is_number("01"));
    ok(is_number("+1"));
}

void test_is_number_negative() {
    ok(is_number("-1"));
}

void test_is_number_false() {
    ok(!is_number("a1"));
    ok(!is_number("1a"));
}

void test_number_argument_1() {
    char argument[MAX_INPUT_LENGTH] = "1.foo";
    char arg[MAX_INPUT_LENGTH];
    int result = number_argument(argument, arg);

    ok(1 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_number_argument_0() {
    char argument[MAX_INPUT_LENGTH] = "0.foo";
    char arg[MAX_INPUT_LENGTH];
    int result = number_argument(argument, arg);

    ok(0 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_number_argument_negative() {
    char argument[MAX_INPUT_LENGTH] = "-1.foo";
    char arg[MAX_INPUT_LENGTH];
    int result = number_argument(argument, arg);

    ok(-1 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_mult_argument_basic() {
    char argument[MAX_INPUT_LENGTH] = "1*foo";
    char arg[MAX_INPUT_LENGTH];
    int result = mult_argument(argument, arg);

    ok(1 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_mult_argument_0() {
    char argument[MAX_INPUT_LENGTH] = "0*foo";
    char arg[MAX_INPUT_LENGTH];
    int result = mult_argument(argument, arg);

    ok(0 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_mult_argument_negative() {
    char argument[MAX_INPUT_LENGTH] = "-1*foo";
    char arg[MAX_INPUT_LENGTH];
    int result = mult_argument(argument, arg);

    ok(-1 == result);
    ok(strcmp(arg, "foo") == 0);
}

void test_one_argument() {
    char argument[MAX_INPUT_LENGTH] = "get foo bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument(argument, arg);

    ok(strcmp(arg, "get") == 0);
    ok(strcmp(result, "foo bar") == 0);
}

void test_one_argument_capitalization() {
    char argument[MAX_INPUT_LENGTH] = "Get Foo Bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument(argument, arg);

    ok(strcmp(arg, "get") == 0);
    ok(strcmp(result, "Foo Bar") == 0);
}

void test_one_argument_successive() {
    char argument[MAX_INPUT_LENGTH] = "get foo bar";
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char arg3[MAX_INPUT_LENGTH];

    char *result1 = one_argument(argument, arg1);
    char *result2 = one_argument(result1, arg2);
    one_argument(result2, arg3);

    ok(strcmp(arg1, "get") == 0);
    ok(strcmp(arg2, "foo") == 0);
    ok(strcmp(arg3, "bar") == 0);
}

void test_one_argument_double_quotes() {
    char argument[MAX_INPUT_LENGTH] = "\"get foo\" bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument(argument, arg);

    ok(strcmp(arg, "get foo") == 0);
    ok(strcmp(result, "bar") == 0);
}

void test_one_argument_single_quotes() {
    char argument[MAX_INPUT_LENGTH] = "'get foo' bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument(argument, arg);

    ok(strcmp(arg, "get foo") == 0);
    ok(strcmp(result, "bar") == 0);
}

void test_one_argument_one_word() {
    char argument[MAX_INPUT_LENGTH] = "get";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument(argument, arg);

    ok(result[0] == '\0');
    ok(strcmp(arg, "get") == 0);
}

void test_one_argument_empty_string() {
    char argument[MAX_INPUT_LENGTH] = "";
    char arg[MAX_INPUT_LENGTH];
    one_argument(argument, arg);

    ok(arg[0] == '\0');
}

void test_one_argument_cs() {
    char argument[MAX_INPUT_LENGTH] = "get foo bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument_cs(argument, arg);

    ok(strcmp(arg, "get") == 0);
    ok(strcmp(result, "foo bar") == 0);
}

void test_one_argument_cs_capitalization() {
    char argument[MAX_INPUT_LENGTH] = "Get Foo Bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument_cs(argument, arg);

    ok(strcmp(arg, "Get") == 0);
    ok(strcmp(result, "Foo Bar") == 0);
}

void test_one_argument_cs_successive() {
    char argument[MAX_INPUT_LENGTH] = "get foo bar";
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char arg3[MAX_INPUT_LENGTH];

    char *result1 = one_argument_cs(argument, arg1);
    char *result2 = one_argument_cs(result1, arg2);
    one_argument_cs(result2, arg3);

    ok(strcmp(arg1, "get") == 0);
    ok(strcmp(arg2, "foo") == 0);
    ok(strcmp(arg3, "bar") == 0);
}

void test_one_argument_cs_double_quotes() {
    char argument[MAX_INPUT_LENGTH] = "\"get foo\" bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument_cs(argument, arg);

    ok(strcmp(arg, "get foo") == 0);
    ok(strcmp(result, "bar") == 0);
}

void test_one_argument_cs_single_quotes() {
    char argument[MAX_INPUT_LENGTH] = "'get foo' bar";
    char arg[MAX_INPUT_LENGTH];
    char *result = one_argument_cs(argument, arg);

    ok(strcmp(arg, "get foo") == 0);
    ok(strcmp(result, "bar") == 0);
}

void run_input_tests() {
    diag("Running input test");

    test_is_number_positive();
    test_is_number_negative();
    test_is_number_false();

    test_number_argument_1();
    test_number_argument_0();
    test_number_argument_negative();

    test_mult_argument_basic();
    test_mult_argument_0();
    test_mult_argument_negative();

    test_one_argument();
    test_one_argument_capitalization();
    test_one_argument_successive();
    test_one_argument_double_quotes();
    test_one_argument_single_quotes();
    test_one_argument_one_word();
    test_one_argument_empty_string();

    test_one_argument_cs();
    test_one_argument_cs_capitalization();
    test_one_argument_cs_successive();
    test_one_argument_cs_double_quotes();
    test_one_argument_cs_single_quotes();

    diag("Finished input test");
}
