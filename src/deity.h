#ifndef MOOSEHEAD_DEITY_H
#define MOOSEHEAD_DEITY_H

void do_deity_msg (char *msg, CHAR_DATA *ch);
bool is_aligned (CHAR_DATA *ch);
void log_deity_favor (CHAR_DATA *ch, CHAR_DATA *alt, int type);
int deity_favor_message (CHAR_DATA *ch, CHAR_DATA *victim, int xp);
int deity_trial_kill (CHAR_DATA *ch, CHAR_DATA *victim, int xp);

#endif //MOOSEHEAD_DEITY_H
