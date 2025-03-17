#include <stdio.h>
#include "merc.h"
#include "db.h"

bool is_equipment(OBJ_INDEX_DATA *object) {
    return object->item_type == ITEM_WEAPON ||
            object->item_type == ITEM_ARMOR;
}

void output_row(OBJ_INDEX_DATA *obj, const char *where) {
    printf("%s, \"%s\", %d, ",
           obj->area->name,
           obj->short_descr,
           obj->level);

    if (obj->item_type == ITEM_WEAPON) {
        printf("weapon, ");
        switch (obj->value[0]) {
            case(WEAPON_EXOTIC) : printf("exotic, "); break;
            case(WEAPON_SWORD)  : printf("sword, ");  break;
            case(WEAPON_DAGGER) : printf("dagger, "); break;
            case(WEAPON_SPEAR)  : printf("spear/staff, ");  break;
            case(WEAPON_MACE)   : printf("mace/club, ");  break;
            case(WEAPON_AXE)    : printf("axe, ");    break;
            case(WEAPON_FLAIL)  : printf("flail, ");  break;
            case(WEAPON_WHIP)   : printf("whip, ");   break;
            case(WEAPON_POLEARM): printf("polearm, ");  break;
            case(WEAPON_GAROTTE): printf("garotte, ");  break;
            default             : printf("unknown");  break;
        }
        if (obj->new_format) {
            printf("%dd%d (average %d), ",
                   obj->value[1],obj->value[2],
                   ((1 + obj->value[2]) * obj->value[1] / 2));
        } else {
            printf("%d to %d (average %d),",
                   obj->value[1], obj->value[2],
                   ((obj->value[1] + obj->value[2] ) / 2));
        }
        printf("%s, ", weapon_bit_name(obj->value[4]));
    } else if (obj->item_type == ITEM_ARMOR) {
        printf("armor, ");
        if (obj->wear_flags & ITEM_WEAR_FINGER) printf("finger, ");
        else if (obj->wear_flags & ITEM_WEAR_NECK) printf("neck, ");
        else if (obj->wear_flags & ITEM_WEAR_BODY) printf("body, ");
        else if (obj->wear_flags & ITEM_WEAR_HEAD) printf("head, ");
        else if (obj->wear_flags & ITEM_WEAR_LEGS) printf("legs, ");
        else if (obj->wear_flags & ITEM_WEAR_FEET) printf("feet, ");
        else if (obj->wear_flags & ITEM_WEAR_HANDS) printf("hands, ");
        else if (obj->wear_flags & ITEM_WEAR_ARMS) printf("arms, ");
        else if (obj->wear_flags & ITEM_WEAR_SHIELD) printf("shield, ");
        else if (obj->wear_flags & ITEM_WEAR_ABOUT) printf("body, ");
        else if (obj->wear_flags & ITEM_WEAR_WAIST) printf("waist, ");
        else if (obj->wear_flags & ITEM_WEAR_WRIST) printf("wrist, ");
        else if (obj->wear_flags & ITEM_WIELD) printf("wield, ");
        else if (obj->wear_flags & ITEM_HOLD) printf("hold, ");
        else if (obj->wear_flags & ITEM_WEAR_FLOAT) printf("float, ");

        printf("%d/%d/%d/%d, none, ",
               obj->value[0],
               obj->value[1],
               obj->value[2],
               obj->value[3]);
    }

    printf("%s, ", extra_bit_name(obj->extra_flags));

    AFFECT_DATA *aff = obj->affected;
    while (aff != NULL) {
        printf("%s %d ",
               affect_loc_name(aff->location),
               aff->modifier);
        aff = aff->next;
    }
    printf(", %s\n", where);
}

void dump_obj_csv() {
    log_string("dump objects initiated");
    printf("area, object name, level, eq type, weapon type/armor position, stats, weapon flags, extra flags, affects, found at\n");
    char where_buf[MAX_INPUT_LENGTH];
    AREA_DATA *area = area_first;
    OBJ_INDEX_DATA *obj;
    RESET_DATA *reset;
    MOB_INDEX_DATA *mob;
    ROOM_INDEX_DATA *room;
    OBJ_INDEX_DATA *container;
    while (area != NULL) {
        reset = area->reset_first;
        while (reset != NULL) {
//            printf("debug: reset data: %c %d %d %d %d\n",
//                   reset->command,
//                   reset->arg1,
//                   reset->arg2,
//                   reset->arg3,
//                   reset->arg4);
            switch (reset->command) {
                case 'M': // mob reset
                    mob = get_mob_index(reset->arg1);
//                    printf("debug: mob: %s\n", mob->short_descr);
                    break;
                case 'O': // object in room
                    obj = get_obj_index(reset->arg1);
                    room = get_room_index(reset->arg3);
                    if (is_equipment(obj)) {
                        sprintf(where_buf, "in room %s", room->name);
                        output_row(obj, where_buf);
                    }
                    break;
                case 'P': // object in object
                    obj = get_obj_index(reset->arg1);
                    container = get_obj_index(reset->arg3);
                    if (is_equipment(obj)) {
                        sprintf(where_buf, "in container %s", container->short_descr);
                        output_row(obj, where_buf);
                    }
                    break;
                case 'G': // give object to mobile
                    obj = get_obj_index(reset->arg1);
                    if (is_equipment(obj)) {
                        sprintf(where_buf, "inventory of %s", mob->short_descr);
                        output_row(obj, where_buf);
                    }
                    break;
                case 'E': // equip object to mobile
                    obj = get_obj_index(reset->arg1);
                    if (is_equipment(obj)) {
                        sprintf(where_buf, "equipped by %s", mob->short_descr);
                        output_row(obj, where_buf);
                    }
                    break;
                default:
                    break;
            }
            reset = reset->next;
        }
        area = area->next;
    }
}