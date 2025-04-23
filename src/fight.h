#ifndef MOOSEHEAD_FIGHT_H
#define MOOSEHEAD_FIGHT_H

void set_fighting (CHAR_DATA *ch, CHAR_DATA *victim);
void one_hit (CHAR_DATA *ch, CHAR_DATA *victim, int dt);
void do_rescue (CHAR_DATA *ch, char *argument);
void do_bash (CHAR_DATA *ch, char *argument);
void do_backstab (CHAR_DATA *ch, char *argument);
void do_flee (CHAR_DATA *ch, char *argument);
void do_murder (CHAR_DATA *ch, char *argument);
void sort_clanner_items (CHAR_DATA *ch, OBJ_DATA *container, OBJ_DATA **loot_start, bool do_linked);
CHAR_DATA *check_is_online (char *name);
bool is_safe (CHAR_DATA *ch, CHAR_DATA *victim);
bool is_safe_steal (CHAR_DATA *ch, CHAR_DATA *victim);
bool is_safe_spell(CHAR_DATA *ch, CHAR_DATA *victim, bool area , int sn);
void violence_update (void);
void multi_hit (CHAR_DATA *ch, CHAR_DATA *victim, int dt);
bool damage (CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt, int class, bool show, bool iOld);
void update_pos (CHAR_DATA *victim);
void stop_fighting (CHAR_DATA *ch, bool fBoth);
void check_killer (CHAR_DATA *ch, CHAR_DATA *victim);
void raw_kill (CHAR_DATA *victim, CHAR_DATA *ch);
bool is_clan_guard (CHAR_DATA *victim);
void make_corpse (CHAR_DATA *ch, CHAR_DATA *killer);

#endif //MOOSEHEAD_FIGHT_H
