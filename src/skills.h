#pragma once

void do_skills (CHAR_DATA *ch, char *argument);
void do_groups (CHAR_DATA *ch, char *argument);
int skill_level	(CHAR_DATA *ch, int sn);
bool parse_gen_groups (CHAR_DATA *ch,char *argument);
void list_group_costs (CHAR_DATA *ch);
void list_group_known (CHAR_DATA *ch);
int exp_per_level (CHAR_DATA *ch, int points);
void check_improve (CHAR_DATA *ch, int sn, bool success, int multiplier);
int group_lookup (const char *name);
void gn_add (CHAR_DATA *ch, int gn);
void gn_remove (CHAR_DATA *ch, int gn);
void group_add (CHAR_DATA *ch, const char *name, bool deduct);
void group_remove (CHAR_DATA *ch, const char *name);
