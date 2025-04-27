#pragma once

char *format_obj_to_char (OBJ_DATA *obj, CHAR_DATA *ch, bool fShort);
void do_look (CHAR_DATA *ch, char *argument);
void do_help (CHAR_DATA *ch, char *argument);
void do_count (CHAR_DATA *ch, char *argument);
void do_exits (CHAR_DATA *ch, char *argument);
void do_affects (CHAR_DATA *ch, char *argument);
void do_surname (CHAR_DATA *ch, char *argument);
void set_title (CHAR_DATA *ch, char *title);
void show_list_to_char (OBJ_DATA *list, CHAR_DATA *ch, bool fShort, bool fShowNothing, bool fExpand);
