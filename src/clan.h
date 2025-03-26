#ifndef MOOSEHEAD_CLAN_H
#define MOOSEHEAD_CLAN_H

void calculate_award_tribute(CLAN_DATA *clan);
void notify_clan(char *string, CLAN_DATA *clan);
bool is_clan_friendly(CHAR_DATA *first, CHAR_DATA *second);

#endif //MOOSEHEAD_CLAN_H
