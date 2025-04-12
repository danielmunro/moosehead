#include <stdio.h>
#include "merc.h"

const char *get_immortal_role(int level) {
    switch (level) {
        case MAX_LEVEL - 0 : return "IMPLEMENTOR";
        case MAX_LEVEL - 1 : return "CREATOR";
        case MAX_LEVEL - 2 : return "SUPREMACY";
        case MAX_LEVEL - 3 : return "DEITY";
        case MAX_LEVEL - 4 : return "GOD";
        case MAX_LEVEL - 5 : return "IMMORTAL";
        case MAX_LEVEL - 6 : return "DEMIGOD";
        case MAX_LEVEL - 7 : return "ANGEL";
        case MAX_LEVEL - 8 : return "AVATAR";
        default: return "";
    }
}
