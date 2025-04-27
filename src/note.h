#pragma once

/*
 * Various note files
 */
#define NOTE_FILE       DATA_DIR "/area/notes.not"
#define IDEA_FILE       DATA_DIR "/area/ideas.not"
#define PENALTY_FILE    DATA_DIR "/area/penal.not"
#define CLAN_FILE       DATA_DIR "/area/clan.not"
#define IMMORTAL_FILE   DATA_DIR "/area/immortal.not"
#define NEWS_FILE       DATA_DIR "/area/news.not"
#define CHANGES_FILE    DATA_DIR "/area/chang.not"
#define OOC_FILE        DATA_DIR "/area/ooc.not"
#define QUEST_FILE	    DATA_DIR "/area/quest.not"
#define BUG_FILE        DATA_DIR "/area/bugs.not"

void do_unread (CHAR_DATA *ch, char *argument);
void do_text (CHAR_DATA *ch, char *argument);
void append_note (NOTE_DATA *pnote);
bool start_long_edit (CHAR_DATA *ch, int limit, int type, char *base_str);
void do_long_edit (CHAR_DATA *ch, char *arg, int type, int edit_type);
void end_long_edit (CHAR_DATA *ch, char **result);

