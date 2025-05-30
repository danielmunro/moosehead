#include <stdio.h>

#include "merc.h"
#include "db.h"
#include "handler.h"
#include "log.h"

bool should_include(OBJ_INDEX_DATA *object) {
    return object->item_type != ITEM_FURNITURE
            && object->item_type != ITEM_TRASH
            && object->item_type != ITEM_CORPSE_NPC
            && object->item_type != ITEM_CORPSE_PC
            && object->item_type != ITEM_FOUNTAIN
            && object->item_type != ITEM_PORTAL
            && object->item_type != ITEM_JUKEBOX
            && object->item_type != ITEM_FORGE;
}

void output_row(FILE *fp, OBJ_INDEX_DATA *obj, const char *area_name, const char *where) {

    fprintf(fp,
            "%s, \"%s\", %d, %s, ",
            area_name,
            obj->short_descr,
            obj->level,
            item_name(obj->item_type));

    if (obj->item_type == ITEM_WEAPON) {
        fprintf(fp,
                "%s, none, ",
                weapon_name(obj->value[0]));
        int damage = avg_weapon_damage(obj->new_format,
                                       obj->value[1],
                                       obj->value[2]);
        if (obj->new_format) {
            fprintf(fp,
                    "%dd%d (average %d), ",
                    obj->value[1],
                    obj->value[2],
                    damage);
        } else {
            fprintf(fp,
                    "%d to %d (average %d),",
                    obj->value[1],
                    obj->value[2],
                    damage);
        }
        fprintf(fp,
                "%s, ",
                weapon_bit_name(obj->value[4]));
    } else if (obj->item_type == ITEM_ARMOR) {
        fprintf(fp,
                "none, %s, %d/%d/%d/%d, none, ",
                wear_bit_name(obj->wear_flags & ~ITEM_TAKE),
                obj->value[0],
                obj->value[1],
                obj->value[2],
                obj->value[3]);
    } else {
        fprintf(fp,
                "none, %s, none, none, ",
                wear_bit_name(obj->wear_flags & ~ITEM_TAKE));
    }

    fprintf(fp,
            "%s, ",
            extra_bit_name(obj->extra_flags));

    AFFECT_DATA *aff = obj->affected;
    while (aff != NULL) {
        fprintf(fp,
                "%s %d ",
                affect_loc_name(aff->location),
                aff->modifier);
        aff = aff->next;
    }

    fprintf(fp,
            ", %s\n", where);
}

void dump_obj_csv() {
    char filename[MAX_INPUT_LENGTH];
    sprintf(filename, "%s/items.csv", DATA_DIR);
    sprintf(log_buf, "generating latest object list CSV to %s", filename);
    log_info(log_buf);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        log_error("cannot write items.csv to data directory");
        return;
    }

    // write the header
    fprintf(fp, "area, name, level, item type, weapon type, armor position, stats, weapon flags, extra flags, affects, found at\n");

    // process resets by game area
    char where_buf[MAX_INPUT_LENGTH];
    AREA_DATA *area = area_first;
    OBJ_INDEX_DATA *obj = NULL;
    RESET_DATA *reset = NULL;
    MOB_INDEX_DATA *mob = NULL;
    ROOM_INDEX_DATA *room = NULL;
    OBJ_INDEX_DATA *container = NULL;
    while (area != NULL) {
        reset = area->reset_first;
        while (reset != NULL) {
            switch (reset->command) {
                case 'M': // mob reset
                    mob = get_mob_index(reset->arg1);
                    if (!mob) {
                        sprintf(log_buf, "error with mob reset :: area: %s, mob: %d",
                                area->name, reset->arg1);
                    }
                    break;
                case 'O': // object in room
                    obj = get_obj_index(reset->arg1);
                    room = get_room_index(reset->arg3);
                    if (!obj || !room) {
                        sprintf(log_buf, "error with object reset :: area: %s, obj: %d (%d), room: %d (%d)",
                                area->name, reset->arg1, !!obj, reset->arg3, !!room);
                        log_error(log_buf);
                    } else if (should_include(obj)) {
                        sprintf(where_buf, "in room %s", room->name);
                        output_row(fp, obj, area->name, where_buf);
                    }
                    break;
                case 'P': // object in object
                    obj = get_obj_index(reset->arg1);
                    container = get_obj_index(reset->arg3);
                    if (!obj || !container) {
                        sprintf(log_buf, "error with object in object reset :: area: %s, obj: %d (%d), room: %d (%d)",
                                area->name, reset->arg1, !!obj, reset->arg3, !!container);
                        log_error(log_buf);
                    } else if (should_include(obj)) {
                        sprintf(where_buf, "in container %s", container->short_descr);
                        output_row(fp, obj, area->name, where_buf);
                    }
                    break;
                case 'G': // give object to mobile
                    obj = get_obj_index(reset->arg1);
                    if (!obj || !mob) {
                        sprintf(log_buf, "error with object in inventory reset :: area: %s, obj: %d (%d), mob: %d",
                                area->name, reset->arg1, !!obj, !!mob);
                        log_error(log_buf);
                    } else if (should_include(obj)) {
                        sprintf(where_buf, "inventory of %s", mob->short_descr);
                        output_row(fp, obj, area->name, where_buf);
                    }
                    break;
                case 'E': // equip object to mobile
                    obj = get_obj_index(reset->arg1);
                    if (!obj || !mob) {
                        sprintf(log_buf, "error with object in equipment reset :: area: %s, obj: %d (%d), mob: %d",
                                area->name, reset->arg1, !!obj, !!mob);
                        log_error(log_buf);
                    } else if (should_include(obj)) {
                        sprintf(where_buf, "equipped by %s", mob->short_descr);
                        output_row(fp, obj, area->name, where_buf);
                    }
                    break;
                default:
                    break;
            }
            reset = reset->next;
        }
        area = area->next;
    }
    fclose(fp);
}