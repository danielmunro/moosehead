#include <stdbool.h>

#include "../src/handler.h"

void test_avg_weapon_damage_new_type() {
    ok(6 == avg_weapon_damage(true, 2, 5));
    ok(42 == avg_weapon_damage(true, 4, 20));
}

void test_avg_weapon_damage_old_type() {
    ok(3 == avg_weapon_damage(false, 2, 5));
    ok(12 == avg_weapon_damage(false, 4, 20));
}

void run_handler_tests() {
    test_avg_weapon_damage_new_type();
    test_avg_weapon_damage_old_type();
}
