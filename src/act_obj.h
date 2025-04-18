#ifndef MOOSEHEAD_ACT_OBJ_H
#define MOOSEHEAD_ACT_OBJ_H

int set_rarity (OBJ_DATA *obj);
void return_clan_gear (CHAR_DATA *ch, OBJ_DATA *corpse);
int get_link_limit (CHAR_DATA *ch);
bool remove_obj (CHAR_DATA *ch, int iWear, bool fReplace);
void wear_obj (CHAR_DATA *ch, OBJ_DATA *obj, bool fReplace);

#endif //MOOSEHEAD_ACT_OBJ_H
