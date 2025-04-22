#ifndef MOOSEHEAD_NOTE_H
#define MOOSEHEAD_NOTE_H

void do_unread (CHAR_DATA *ch, char *argument);
void do_text (CHAR_DATA *ch, char *argument);
void append_note (NOTE_DATA *pnote);
bool start_long_edit (CHAR_DATA *ch, int limit, int type, char *base_str);
void do_long_edit (CHAR_DATA *ch, char *arg, int type, int edit_type);
void end_long_edit (CHAR_DATA *ch, char **result);

#endif //MOOSEHEAD_NOTE_H
