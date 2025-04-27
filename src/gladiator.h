#pragma once

/*
 * Structure types.
 */
typedef struct  gladiator_info_data     GLADIATOR_INFO_DATA;

struct  gladiator_info_data
{
    bool	started;
    int         time_left;
    int         min_level;
    int         max_level;
    int         type;
    int		playing;
    int		team_counter;
    int		gladiator_score;
    int		barbarian_score;
    int		bet_counter;
    int		bet_total;
    int  	total_levels;
    int 	total_wins;
    int 	total_plays;
    int		num_of_glads;
    bool	blind;
    bool        exper;
    bool        WNR;
};

/*
 * Global variables.
 */
extern          GLADIATOR_INFO_DATA     gladiator_info;

void set_glad_name (CHAR_DATA *ch);
void gladiator_rename_all (void);
void  gladiator_update (void);
void  remove_gladiator (CHAR_DATA *ch);
void  gladiator_left_arena (CHAR_DATA *ch, bool DidQuit);
void  gladiator_talk (char *txt);
void  gladiator_talk_ooc (char *txt);
void  gladiator_winner (CHAR_DATA *ch);
void  gladiator_kill (CHAR_DATA *victim, CHAR_DATA *ch);
