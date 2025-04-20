#ifndef MOOSEHEAD_ACT_COMM_H
#define MOOSEHEAD_ACT_COMM_H

void do_immtalk (CHAR_DATA *ch, char *argument);
void send_timestamp (CHAR_DATA *ch, bool send_now, bool global);
void do_order (CHAR_DATA *ch, char *argument);
void do_split (CHAR_DATA *ch, char *argument);
void do_yell (CHAR_DATA *ch, char *argument);
void do_say (CHAR_DATA *ch, char *argument);
void do_gossip (CHAR_DATA *ch, char *argument);
void do_ooc (CHAR_DATA *ch, char *argument);
void do_question (CHAR_DATA *ch, char *argument);
void do_answer (CHAR_DATA *ch, char *argument);
void do_auction (CHAR_DATA *ch, char *argument);
void do_music (CHAR_DATA *ch, char *argument);
void do_quest (CHAR_DATA *ch, char *argument);
void do_reply (CHAR_DATA *ch, char *argument);
void do_tell (CHAR_DATA *ch, char *argument);
void do_clantalk (CHAR_DATA *ch, char *argument);
void do_grats (CHAR_DATA *ch, char *argument);
void do_gtell (CHAR_DATA *ch, char *argument);
void do_quit (CHAR_DATA *ch, char *argument);
void do_save (CHAR_DATA *ch, char *argument);

#endif //MOOSEHEAD_ACT_COMM_H
