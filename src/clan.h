#pragma once

void calculate_award_tribute(CLAN_DATA *clan);
void notify_clan(char *string, CLAN_DATA *clan);
bool notify_clan_leaders(char *string, CLAN_DATA *clan, bool offline);
bool notify_clan_char(char *string, CLAN_CHAR *target, bool offline);
bool is_clan_friendly(CHAR_DATA *first, CHAR_DATA *second);
void load_clans(void);
int calculate_bonus_merit (CHAR_DATA *ch, bool new_join);
void set_clan_skills (CHAR_DATA *ch);
bool clan_kill_type (CHAR_DATA *killer, CHAR_DATA *victim);
void remove_clan_member (CLAN_CHAR *cchar);
void add_clan_member (CLAN_DATA *clan, CHAR_DATA *ch, int rank);
CLAN_CHAR *find_char_clan (char *name);
