#ifndef MOOSEHEAD_HANDLER_H
#define MOOSEHEAD_HANDLER_H

bool tick_pulse_command(CHAR_DATA *ch);
void affect_modify(CHAR_DATA *ch, AFFECT_DATA *paf, bool fAdd, int AppType);
long wiznet_lookup (const char *name);
char *extra2_bit_name(int extra_flags2);
bool has_boat (CHAR_DATA *ch);
int liq_lookup (const char *name);

#endif //MOOSEHEAD_HANDLER_H
