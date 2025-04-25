#include "../src/const.h"
#include "../src/handler.h"
#include "../src/magic.h"
#include "../src/skills.h"

void test_skill_level_only_reclass_has_skill() {
    // given
    CHAR_DATA ch;

    // when
    ch.race = race_lookup("human");
    ch.class = class_lookup("samurai");
    int sn = skill_lookup("chee");

    // then - the skill level should be determined by the primary class
    ok(skill_table[sn].skill_level[ch.class] == skill_level(&ch, sn));
}

void run_skills_tests() {
    test_skill_level_only_reclass_has_skill();
}
