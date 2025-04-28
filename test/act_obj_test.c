#include <gc.h>

#include "../src/act_obj.h"
#include "../src/handler.h"

// Mock functions and data needed for testing
CHAR_DATA *create_mock_char() {
    CHAR_DATA *ch = GC_MALLOC(sizeof(CHAR_DATA));
    ch->name = strdup("TestChar");
    ch->level = 50;
    ch->gold = 1000;
    ch->silver = 1000;
    return ch;
}

OBJ_DATA *create_mock_obj(int item_type, int wear_loc, int damaged) {
    OBJ_DATA *obj = GC_MALLOC(sizeof(OBJ_DATA));
    OBJ_INDEX_DATA *pIndex = GC_MALLOC(sizeof(OBJ_INDEX_DATA));
    
    obj->name = strdup("test_object");
    obj->short_descr = strdup("a test object");
    obj->description = strdup("A test object is here.");
    obj->pIndexData = pIndex;
    obj->item_type = item_type;
    obj->wear_loc = wear_loc;
    obj->damaged = damaged;
    obj->level = 10;
    
    return obj;
}

// Test for set_rarity function
void test_set_rarity() {
    // Test case 1: Standard item
    OBJ_DATA *obj = create_mock_obj(ITEM_WEAPON, -1, 0);
    int rarity = set_rarity(obj);
    ok(rarity == RARITY_STOCK, "Standard item should have RARITY_STOCK");
    
    // Test case 2: Impossible item (with IMM_LOAD flag)
    obj = create_mock_obj(ITEM_WEAPON, -1, 0);
    SET_BIT(obj->extra_flags, ITEM_IMM_LOAD);
    rarity = set_rarity(obj);
    ok(rarity == RARITY_IMPOSSIBLE, "Item with IMM_LOAD flag should have RARITY_IMPOSSIBLE");
}

// Test for add_bonuses and remove_bonuses functions
void test_bonuses() {
    CHAR_DATA *ch = create_mock_char();
    
    // Test case 1: Damaged item should not add bonuses
    OBJ_DATA *damaged_obj = create_mock_obj(ITEM_WEAPON, WEAR_WIELD, 100);
    damaged_obj->carried_by = ch;

    add_bonuses(ch, damaged_obj);
    // We can't easily test the effect, but we can verify it doesn't crash
    pass("add_bonuses with damaged item doesn't crash");
    
    // Test case 2: Non-worn item should not add bonuses
    OBJ_DATA *unworn_obj = create_mock_obj(ITEM_WEAPON, -1, 0);
    add_bonuses(ch, unworn_obj);
    pass("add_bonuses with unworn item doesn't crash");

    // Test case 3: Remove bonuses from damaged item
    remove_bonuses(ch, damaged_obj);
    pass("remove_bonuses with damaged item doesn't crash");
}

// Test for is_repairable function
void test_is_repairable() {
    // Test case 1: Weapon should be repairable
    OBJ_DATA *weapon = create_mock_obj(ITEM_WEAPON, -1, 0);
    ok(is_repairable(weapon) == true, "Weapons should be repairable");
    
    // Test case 2: Armor should be repairable
    OBJ_DATA *armor = create_mock_obj(ITEM_ARMOR, -1, 0);
    ok(is_repairable(armor) == true, "Armor should be repairable");
    
    // Test case 3: Food should not be repairable
    OBJ_DATA *food = create_mock_obj(ITEM_FOOD, -1, 0);
    ok(is_repairable(food) == false, "Food should not be repairable");
    
    // Test case 4: Potion should not be repairable
    OBJ_DATA *potion = create_mock_obj(ITEM_POTION, -1, 0);
    ok(is_repairable(potion) == false, "Potions should not be repairable");
}

// Test for check_repair_obj function
void test_check_repair_obj() {
    CHAR_DATA *ch = create_mock_char();
    CHAR_DATA *weapon_smith = create_mock_char();
    CHAR_DATA *armor_smith = create_mock_char();
    
    // Set up weapon smith and armor smith
    SET_BIT(weapon_smith->act, ACT_IS_WEAPONSMITH);
    SET_BIT(armor_smith->act, ACT_IS_ARMOURER);
    
    // Test case 1: Undamaged item
    OBJ_DATA *undamaged_obj = create_mock_obj(ITEM_WEAPON, -1, 0);
    int cost = check_repair_obj(undamaged_obj, ch, weapon_smith, armor_smith, false);
    ok(cost == 0, "Undamaged item should have repair cost of 0");
    
    // Test case 2: Slightly damaged weapon
    OBJ_DATA *damaged_weapon = create_mock_obj(ITEM_WEAPON, -1, 50);
    cost = check_repair_obj(damaged_weapon, ch, weapon_smith, armor_smith, false);
    ok(cost > 0, "Damaged weapon should have repair cost > 0");
    
    // Test case 3: Heavily damaged armor
    OBJ_DATA *damaged_armor = create_mock_obj(ITEM_ARMOR, -1, 150);
    cost = check_repair_obj(damaged_armor, ch, weapon_smith, armor_smith, false);
    ok(cost > 0, "Damaged armor should have repair cost > 0");
    
    // Test case 4: Item that can't be repaired
    OBJ_DATA *unrepairable = create_mock_obj(ITEM_FOOD, -1, 50);
    cost = check_repair_obj(unrepairable, ch, weapon_smith, armor_smith, false);
    ok(cost == 0, "Unrepairable item should have repair cost of 0");
}

void run_act_obj_tests() {
    diag("Running act_obj tests");
    
    test_set_rarity();
    test_bonuses();
    test_is_repairable();
    test_check_repair_obj();
    
    diag("Finished act_obj tests");
}
