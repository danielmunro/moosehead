#ifndef MOOSEHEAD_LIVE_EDIT_H
#define MOOSEHEAD_LIVE_EDIT_H

#include "structs.h"

void verify_price_table(void);
bool check_legal_hall(ROOM_INDEX_DATA *room);
void read_to_tilde(FILE *fp, char **string);
void update_room_sign(CLAN_DATA *clan, ROOM_INDEX_DATA *room);
void fwrite_plan_obj(FILE *fp, PLAN_DATA *obj);
void fwrite_room_exits(FILE *fp, PLAN_DATA *obj);

#endif //MOOSEHEAD_LIVE_EDIT_H
