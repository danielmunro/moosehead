#ifndef MOOSEHEAD_ACT_COMM_H
#define MOOSEHEAD_ACT_COMM_H

void do_immtalk (CHAR_DATA *ch, char *argument);
void send_timestamp (CHAR_DATA *ch, bool send_now, bool global);
void do_order (CHAR_DATA *ch, char *argument);
void do_split (CHAR_DATA *ch, char *argument);
void do_yell (CHAR_DATA *ch, char *argument);
void do_say (CHAR_DATA *ch, char *argument);
void do_quit (CHAR_DATA *ch, char *argument);
void do_save (CHAR_DATA *ch, char *argument);
void do_clantalk (CHAR_DATA *ch, char *argument);

#endif //MOOSEHEAD_ACT_COMM_H
