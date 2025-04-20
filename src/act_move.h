#ifndef MOOSEHEAD_ACT_MOVE_H
#define MOOSEHEAD_ACT_MOVE_H

void do_stand (CHAR_DATA *ch, char *argument);
void do_recall (CHAR_DATA *ch, char *argument);
void do_open (CHAR_DATA *ch, char *argument);
void do_close (CHAR_DATA *ch, char *argument);
void do_wake (CHAR_DATA *ch, char *argument);
void do_dismount (CHAR_DATA *ch, char *argument);
bool recall (CHAR_DATA *ch, char *argument, bool fPray);
void action_ambush (CHAR_DATA *ch, char *argument);
int find_door (CHAR_DATA *ch, char *arg);
bool has_key (CHAR_DATA *ch, int key);

#endif //MOOSEHEAD_ACT_MOVE_H
