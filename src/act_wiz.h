#pragma once

void remove_highlander (CHAR_DATA *ch, CHAR_DATA *victim);
void do_outfit (CHAR_DATA *ch, char *argument);
void do_echo (CHAR_DATA *ch, char *argument);
void do_return (CHAR_DATA *ch, char *argument);
void wiznet (char *string, CHAR_DATA *ch, OBJ_DATA *obj, long flag,
             long flag_skip, int min_level);
void pnet (char *string, CHAR_DATA *ch, OBJ_DATA *obj, long flag,
           long flag_skip, int min_level);
