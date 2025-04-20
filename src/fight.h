#ifndef MOOSEHEAD_FIGHT_H
#define MOOSEHEAD_FIGHT_H

void set_fighting (CHAR_DATA *ch, CHAR_DATA *victim);
void one_hit (CHAR_DATA *ch, CHAR_DATA *victim, int dt);
void do_rescue (CHAR_DATA *ch, char *argument);
void do_bash (CHAR_DATA *ch, char *argument);
void do_backstab (CHAR_DATA *ch, char *argument);
void do_flee (CHAR_DATA *ch, char *argument);
void do_murder (CHAR_DATA *ch, char *argument);

#endif //MOOSEHEAD_FIGHT_H
