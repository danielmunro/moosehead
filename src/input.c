/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "macros.h"

void string_to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

/*
 * Return true if an argument is completely numeric.
 */
bool is_number(char *arg) {
    if (*arg == '\0') {
        return false;
    }

    if (*arg == '+' || *arg == '-') {
        arg++;
    }

    for (; *arg != '\0'; arg++) {
        if (!isdigit(*arg)) {
            return false;
        }
    }

    return true;
}

/*
 * Given a string like 14.foo, return 14 and 'foo'
 */
int number_argument(char *argument, char *arg) {
    char *pdot;
    int number;

    for (pdot = argument; *pdot != '\0'; pdot++) {
        if (*pdot == '.') {
            *pdot = '\0';
            number = atoi(argument);
            *pdot = '.';
            strcpy(arg, pdot + 1);
            return number;
        }
    }

    strcpy(arg, argument);
    return 1;
}

/*
 * Given a string like 14*foo, return 14 and 'foo'
 */
int mult_argument(char *argument, char *arg) {
    char *pdot;
    int number;

    for (pdot = argument; *pdot != '\0'; pdot++) {
        if (*pdot == '*') {
            *pdot = '\0';
            number = atoi(argument);
            *pdot = '*';
            strcpy(arg, pdot + 1);
            return number;
        }
    }

    strcpy(arg, argument);
    return 1;
}

/*
 * Pick off one argument from a string and return the rest.
 * Understands quotes.
 */
char *one_argument_cs(char *argument, char *arg_first) {
    char cEnd;

    while (isspace(*argument)) {
        argument++;
    }

    cEnd = ' ';
    if (*argument == '\'' || *argument == '"') {
        cEnd = *argument++;
    }

    while (*argument != '\0') {
        if (*argument == cEnd) {
            argument++;
            break;
        }
        *arg_first = *argument;
        arg_first++;
        argument++;
    }
    *arg_first = '\0';

    while (isspace(*argument)) {
        argument++;
    }

    return argument;
}

/*
 * Pick off one argument from a string and return the rest.
 * Understands quotes.  The first argument is converted to lower case.
 */
char *one_argument(char *argument, char *arg_first) {
    char *result = one_argument_cs(argument, arg_first);
    string_to_lower(arg_first);
    return result;
}
