#pragma once

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

void set_from_previous_menu(CHAR_DATA *ch);

void set_previous_menu(CHAR_DATA *ch);

