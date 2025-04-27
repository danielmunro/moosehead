#pragma once

int set_rarity (OBJ_DATA *obj);
void return_clan_gear (CHAR_DATA *ch, OBJ_DATA *corpse);
int get_link_limit (CHAR_DATA *ch);
void remove_all_objs (CHAR_DATA *ch, bool verbose);
bool remove_obj (CHAR_DATA *ch, int iWear, bool fReplace);
void wear_obj (CHAR_DATA *ch, OBJ_DATA *obj, bool fReplace);
void get_obj (CHAR_DATA *ch, OBJ_DATA *obj, OBJ_DATA *container);
void do_get (CHAR_DATA *ch, char *argument);
void do_sacrifice (CHAR_DATA *ch, char *argument);
void do_wear (CHAR_DATA *ch, char *argument);
void unlink_item (CHAR_DATA *ch, OBJ_DATA *obj);
void do_link (CHAR_DATA *ch, char *argument);
void do_unlink (CHAR_DATA *ch, char *argument);
void do_linksafe (CHAR_DATA *ch, char *argument);
void steal (CHAR_DATA *ch, char *arg1, CHAR_DATA *victim);
bool can_loot (CHAR_DATA *ch, OBJ_DATA *obj, bool loot_check);
void remove_bonuses (CHAR_DATA *ch, OBJ_DATA *obj);
