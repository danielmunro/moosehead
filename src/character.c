#include "merc.h"

bool is_immortal(int level) {
    return level > MAX_LEVEL - 8;
}

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

const char *get_race_size(int size) {
    switch (size) {
        case SIZE_TINY:
            return "tiny";
        case SIZE_SMALL:
            return "small";
        case SIZE_MEDIUM:
            return "medium";
        case SIZE_LARGE:
            return "large";
        case SIZE_HUGE:
            return "huge";
        case SIZE_GIANT:
            return "gigantic";
        default:
            return "unknown";
    }
}
