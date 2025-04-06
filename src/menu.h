#ifndef MOOSEHEAD_MENU_H
#define MOOSEHEAD_MENU_H

#define MAX_MENU_ITEMS 64

typedef void MENU_FUN (CHAR_DATA *ch, int menu_id);

typedef enum {
    ONE_COLUMN,
    TWO_COLUMNS
} MenuLayout;

typedef struct {
    char *text;
    char *context;
    int id;
    MENU_FUN *menu_fun;
} MENU_ITEM;

typedef struct {
    MenuLayout layout;
    int column_width;
    MENU_ITEM items[MAX_MENU_ITEMS];
} MENU_DATA;

void do_menu(CHAR_DATA *ch, char *arg);
void do_menu_refactor(CHAR_DATA *ch, char *arg);

#endif //MOOSEHEAD_MENU_H
