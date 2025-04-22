#ifndef MOOSEHEAD_LIVE_EDIT_H
#define MOOSEHEAD_LIVE_EDIT_H

void verify_price_table (void);
bool check_legal_hall (ROOM_INDEX_DATA *room);
void read_to_tilde (FILE *fp, char **string);
void update_room_sign (CLAN_DATA *clan, ROOM_INDEX_DATA *room);
void fwrite_plan_obj (FILE *fp, PLAN_DATA *obj);
void fwrite_room_exits (FILE *fp, PLAN_DATA *obj);
void edit_stop (CHAR_DATA *ch);
PLAN_DATA *find_edit_obj_by_index (PLAN_DATA *start, int type, int plan_index);

#endif //MOOSEHEAD_LIVE_EDIT_H
