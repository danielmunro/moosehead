#ifndef MOOSEHEAD_DB_H
#define MOOSEHEAD_DB_H

/* files used in db.c */
typedef struct area_name_data AREA_NAME_DATA;
struct area_name_data {
  AREA_NAME_DATA *next;
  char *name;
};

/* vals from db.c */
extern bool fBootDb;
extern int    newmobs;
extern int    newobjs;
extern MOB_INDEX_DATA   * mob_index_hash          [MAX_KEY_HASH];
extern OBJ_INDEX_DATA   * obj_index_hash          [MAX_KEY_HASH];
extern ROOM_INDEX_DATA  * room_index_hash         [MAX_KEY_HASH];

extern int     top_affect;
extern int     top_area;
extern int     top_ed;
extern int     top_exit;
extern int     top_help;
extern int     top_recipe;
extern int     top_mob_index;
extern int     top_obj_index;
extern int     top_reset;
extern int     top_room;
extern int     top_shop;
extern int     mobile_count;
extern int     newmobs;
extern int     newobjs;

extern AREA_DATA  * area_first, * area_last;
extern AREA_NAME_DATA  *area_name_first, *area_name_last;

extern int  social_count;

void boot_db (void);
void area_update (void);
void MobIndexToInstance (CHAR_DATA *mob, MOB_INDEX_DATA *pMobIndex);
void ObjIndexToInstance (OBJ_DATA *obj, OBJ_INDEX_DATA *pObjIndex, int level, bool favored);
CHAR_DATA *create_mobile (MOB_INDEX_DATA *pMobIndex);
void clone_mobile (CHAR_DATA *parent, CHAR_DATA *clone);
OBJ_DATA *create_object (OBJ_INDEX_DATA *pObjIndex, int level, bool favored);
void clone_object (OBJ_DATA *parent, OBJ_DATA *clone);
char *get_extra_descr (const char *name, EXTRA_DESCR_DATA *ed);
MOB_INDEX_DATA *get_mob_index (int vnum);
OBJ_INDEX_DATA *get_obj_index (int vnum);
ROOM_INDEX_DATA *get_room_index (int vnum);
void rename_area (char *strArea);
void select_bounty (int qualifier);

char fread_letter (FILE *fp);
int fread_number (FILE *fp);
long fread_flag (FILE *fp);
char *fread_string (FILE *fp);
char *fread_string_eol (FILE *fp);
void fread_to_eol (FILE *fp);
char *fread_word (FILE *fp);
long flag_convert (char letter);
void *alloc_perm (int sMem);
void free_mem (void *pMem, int sMem);
void free_string (char *pstr);

void  convert_mob(MOB_INDEX_DATA *mob);
void  convert_obj(OBJ_INDEX_DATA *obj);

char *str_dup(const char *str);

int number_fuzzy (int number);
int number_range (int from, int to);
int number_percent (void);
int number_door (void);
int number_bits (int width);
long number_mm (void);
int dice (int number, int size);
int interpolate (int level, int value_00, int value_32);
void smash_tilde (char *str);
bool str_cmp (const char *astr, const char *bstr);
bool str_prefix (const char *astr, const char *bstr);
bool str_infix (const char *astr, const char *bstr);
bool str_suffix (const char *astr, const char *bstr);
char *capitalize (const char *str);
void append_file (CHAR_DATA *ch, char *file, char *str);

void bug (const char *str, int param);
int get_area_min_vnum (AREA_DATA *area);
int get_area_max_vnum (AREA_DATA *area);
RECIPE_DATA * get_recipe_data (int recipe_number);
void tail_chain (void);

/* macro for flag swapping */
#define GET_UNSET(flag1,flag2)  (~(flag1)&((flag1)|(flag2)))
#define MAGIC_NUM 52571214

char *print_flags (long flag);
void do_collate(CHAR_DATA *ch, char *argument);
void save_area ( CHAR_DATA *ch, AREA_DATA *pArea );
void update_area_list ( CHAR_DATA *ch, char *strArea );

#endif //MOOSEHEAD_DB_H
