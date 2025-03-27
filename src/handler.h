#ifndef MOOSEHEAD_HANDLER_H
#define MOOSEHEAD_HANDLER_H

#include "structs.h"

bool tick_pulse_command(CHAR_DATA *ch);
void affect_modify(CHAR_DATA *ch, AFFECT_DATA *paf, bool fAdd, int AppType);
long wiznet_lookup (const char *name);
char *extra2_bit_name(int extra_flags2);

#endif //MOOSEHEAD_HANDLER_H
