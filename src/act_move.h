#pragma once

void do_stand (CHAR_DATA *ch, char *argument);
void do_recall (CHAR_DATA *ch, char *argument);
void do_open (CHAR_DATA *ch, char *argument);
void do_close (CHAR_DATA *ch, char *argument);
void do_wake (CHAR_DATA *ch, char *argument);
void do_dismount (CHAR_DATA *ch, char *argument);
void do_abolish (CHAR_DATA *ch, char *argument);
bool recall (CHAR_DATA *ch, char *argument, bool fPray);
void action_ambush (CHAR_DATA *ch, char *argument);
int find_door (CHAR_DATA *ch, char *arg);
bool has_key (CHAR_DATA *ch, int key);
void move_char (CHAR_DATA *ch, int door, bool follow);
void fade (CHAR_DATA *ch, char *argument);
