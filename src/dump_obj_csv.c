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
        printf("weapon, %s, ", weapon_name(obj->value[0]));
        int damage = avg_weapon_damage(obj->new_format,
                                       obj->value[1],
                                       obj->value[2]);
        if (obj->new_format) {
            printf("%dd%d (average %d), ",
                   obj->value[1],
                   obj->value[2],
                   damage);
        } else {
            printf("%d to %d (average %d),",
                   obj->value[1],
                   obj->value[2],
                   damage);
        }
        printf("%s, ", weapon_bit_name(obj->value[4]));
    } else if (obj->item_type == ITEM_ARMOR) {
        printf("armor, %s, %d/%d/%d/%d, none, ",
               wear_bit_name(obj->wear_flags & ~ITEM_TAKE),
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