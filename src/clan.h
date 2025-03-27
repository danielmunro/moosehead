#ifndef MOOSEHEAD_CLAN_H
#define MOOSEHEAD_CLAN_H

#include "structs.h"

void calculate_award_tribute(CLAN_DATA *clan);
void notify_clan(char *string, CLAN_DATA *clan);
bool notify_clan_leaders(char *string, CLAN_DATA *clan, bool offline);
bool notify_clan_char(char *string, CLAN_CHAR *target, bool offline);
bool is_clan_friendly(CHAR_DATA *first, CHAR_DATA *second);
void load_clans(void);

#endif //MOOSEHEAD_CLAN_H
