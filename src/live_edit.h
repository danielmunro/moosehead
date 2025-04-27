#pragma once

void verify_price_table (void);
bool check_legal_hall (ROOM_INDEX_DATA *room);
void read_to_tilde (FILE *fp, char **string);
void update_room_sign (CLAN_DATA *clan, ROOM_INDEX_DATA *room);
void fwrite_plan_obj (FILE *fp, PLAN_DATA *obj);
void fwrite_room_exits (FILE *fp, PLAN_DATA *obj);
void edit_stop (CHAR_DATA *ch);
PLAN_DATA *find_edit_obj_by_index (PLAN_DATA *start, int type, int plan_index);
void set_obj_cost (CHAR_DATA *ch, PLAN_DATA *obj, bool hedit, bool override);
bool save_hall (char *clan_name, PLAN_DATA *plans, bool save_immediately);
void do_save_clan (CLAN_DATA *clan);
void save_clan (CHAR_DATA *ch, bool save_c, bool save_h, bool hedit);
void fread_clan_hall (FILE *fp, PLAN_DATA **head, CLAN_DATA *clan);
void respawn_plan_obj (PLAN_DATA *obj, PLAN_DATA *start, bool show_creation);
void clear_string (char **str, char *new_str);
void do_hedit (CHAR_DATA *ch, char *argument);
void do_pedit (CHAR_DATA *ch, char *argument);
