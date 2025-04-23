#ifndef MOOSEHEAD_EFFECTS_H
#define MOOSEHEAD_EFFECTS_H

void acid_effect (void *vo, int level, int dam, int target);
void cold_effect (void *vo, int level, int dam, int target);
void fire_effect (void *vo, int level, int dam, int target);
void holy_effect (CHAR_DATA *victim, int level, int align, CHAR_DATA *ch);
void poison_effect (void *vo, int level, int dam, int target);
void shock_effect (void *vo, int level, int dam, int target);
void trap_effect (CHAR_DATA *ch, AFFECT_DATA *paf);

#endif //MOOSEHEAD_EFFECTS_H
