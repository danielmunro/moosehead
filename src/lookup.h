#define MAX_IMM_COMM 27

#include "tables.h"

int flag_lookup (const char *name, const struct flag_type *flag_table);
CLAN_DATA* clan_lookup (const char *name);
int nonclan_lookup (const char *name);
int gift_lookup (const char *name);
int position_lookup (const char *name);
int sex_lookup (const char *name);
int immc_lookup (const char *name);
int size_lookup (const char *name);
