#ifndef MOOSEHEAD_SAVE_H
#define MOOSEHEAD_SAVE_H

void save_char_obj (CHAR_DATA *ch);
bool load_char_obj (DESCRIPTOR_DATA *d, char *name);
void save_pits (void);
void load_pits (void);

#endif //MOOSEHEAD_SAVE_H
