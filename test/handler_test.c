#include <stdbool.h>

#include "../src/handler.h"

void test_avg_weapon_damage_new_type() {
    ok(6 == avg_weapon_damage(true, 2, 5), "Avg weapon damage calculation is correct with new type");
    ok(42 == avg_weapon_damage(true, 4, 20), "Avg weapon damage calculation is correct with new type");
}

void test_avg_weapon_damage_old_type() {
    ok(3 == avg_weapon_damage(false, 2, 5), "Avg weapon damage calculation is correct with old type");
    ok(12 == avg_weapon_damage(false, 4, 20), "Avg weapon damage calculation is correct with old type");
}

void run_handler_tests() {
    diag("Running handler test");

    test_avg_weapon_damage_new_type();
    test_avg_weapon_damage_old_type();

    diag("Finished handler test");
}
