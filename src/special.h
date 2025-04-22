#ifndef MOOSEHEAD_SPECIAL_H
#define MOOSEHEAD_SPECIAL_H

void bounty_admin_claim (CHAR_DATA *ch, CHAR_DATA *shade, OBJ_DATA *obj);
bool spec_rainbow (CHAR_DATA *creature);
bool spec_thief (CHAR_DATA *ch);
bool spec_cast_mage (CHAR_DATA *ch);
bool spec_cast_cleric (CHAR_DATA *ch);
bool spec_guard_d (CHAR_DATA *ch);

bool is_bounty_target (CHAR_DATA *victim, bool kill);
void describe_mob_bounty (CHAR_DATA *target, CHAR_DATA *teller, bool just_started);
bool is_shaded (CHAR_DATA *shade);
void remove_shaded_room (CHAR_DATA *shade);
SPEC_FUN *spec_lookup (const char *name);
char *spec_name (SPEC_FUN *function);
void quest_handler (CHAR_DATA *quest_npc, CHAR_DATA *ch, OBJ_DATA *obj, int quest, int update);
void log_quest_detail (char *buf, int quest);

#endif //MOOSEHEAD_SPECIAL_H
