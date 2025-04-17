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
 
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "merc.h"
#include "tables.h"

/* for clans */
const struct clan_type clan_table[] =
{
    {   "",             "",             ROOM_VNUM_ALTAR,  false, true, false  },
    {   "loner",   "[ {DLoner {x", ROOM_VNUM_MATOOK, false, true, true },
    {	"outcast", "[{DOutcast{x",  	ROOM_VNUM_MATOOK, false, true, true   },
    {   "demise",  "[{DDemise {x",    ROOM_VNUM_DEMISE,   false, false,true   },
    {   "honor",   "[ {DHonor {x",    ROOM_VNUM_HONOR,    false, false,true   },
    {   "posse",   "[ {DPosse {x",    ROOM_VNUM_POSSE,    false, false,true   },
    {   "avarice", "[{DAvarice{x",   ROOM_VNUM_AVARICE,  false, false, true  },
    {   "zealot",  "[{DZealot {x",   ROOM_VNUM_ZEALOT,   false, false, true  },
    {   "warlock", "[{DWarlock{x",   ROOM_VNUM_WARLOCK,  false, false, true },
    {   "valor",   "[{D Valor {x",   ROOM_VNUM_VALOR,   false, false, true },
    {   "phoenix", "[{DPhoenix{x",    ROOM_VNUM_PHOENIX,  false, false, true },
    {   "riders",  "[{DRiders {x",   ROOM_VNUM_RIDERS,	  false, false, true },
    {   "mcdugal", "[{DMcDugal{x",   ROOM_VNUM_RIDERS,    false, false, true },
    {   "hunter",  "[{DHunter {x",   ROOM_VNUM_HUNTER,    false, false, true },
    {   "temp",    "[{DTemp   {x",     ROOM_VNUM_ALTAR,	  false, false, true },
    {   "smurf",   "[ {DSmurf {x",   ROOM_VNUM_MATOOK,  false, false, true },
    {   "matook",  "({BMatook{x)",    ROOM_VNUM_MATOOK,  false, true,false   },
    {   "newbie",  "({cNewbie{x)",    ROOM_VNUM_ALTAR,  false, true,false   },
    {   "circle",  "({DCircle{x)",    ROOM_VNUM_ALTAR,  false, true,false   },
    {   "camorra",  "({DCamorra{x)",    ROOM_VNUM_ALTAR,  false, true,false   },
    {   "legion",  "({DLegion{x)",    ROOM_VNUM_ALTAR,  false, true,false   },
    {   "macleod",  "({DMacLeod{x)",    ROOM_VNUM_ALTAR,  false, true,false   }
};

/* for assigning IMM commands */
const struct imm_command_type imm_command_table[] =
{
    { "sockets",	ICG_JUDGE,	A },
    { "violate",	ICG_ADMIN,	B },
    { "allow",		ICG_JUDGE,	C },
    { "ban",		ICG_JUDGE,	D },
    { "deny",		ICG_JUDGE,	E },
    { "bflag",		ICG_ADMIN,	F },
    { "disconnect",	ICG_JUDGE,	G },
    { "dweeb",		ICG_JUDGE,	H },
    { "flag",		ICG_QUEST,	I },
    { "freeze",		ICG_JUDGE,	J },
    { "fuck",		ICG_JUDGE,	K },
    { "ident",		ICG_JUDGE,	L },
    { "permban",	ICG_JUDGE,	M },
    { "set",		ICG_QUEST,	N },
    { "wizlock",	ICG_ADMIN,	O },
    { "load",		ICG_QUEST,	P },
    { "newlock",	ICG_JUDGE,	Q },
    { "pardon",		ICG_JUDGE,	S },
    { "restore",	ICG_QUEST,	T },
    { "slay",		ICG_JUDGE,	U },
    { "gecho",		ICG_ADMIN,	V },
    { "log",		ICG_JUDGE,	W },
    { "peace",		ICG_QUEST,	X },
    { "return",		ICG_QUEST,	Y },
    { "snoop",		ICG_JUDGE,	Z },
    { "switch",		ICG_QUEST,	Y },
    { "clone",		ICG_QUEST,	P }

};


/* for deities Remove and add to const.c for comm.c 
const struct deity_type deity_table[] =
{
    {	"mojo",		"Mojo",		{"recall"},
	ALIGN_NONE,	false	},
    {	"matook",	"Matook",	{"recall","patience"},
	ALIGN_NONE,	false	},
    {	"bolardari",	"Bolardari",	{"recall","random"},
	ALIGN_NEUTRAL,	false	},
    {	"megena",	"Megena",	{"recall","nurture","meld"},
	ALIGN_GOOD,	false	},
    {	"huitzilopochtli", "Huitzilopochtli", {"recall","reanimation"},
	ALIGN_EVIL,	false	},
    {	"xochipili",	"Xochipili",	{"recall","opiate"},
	ALIGN_NONE,	false	},
    {	"paladine",	"Paladine",	{"recall","bravery","stature"},
	ALIGN_GOOD,	true	},
    {   "loki",		"Loki",		{"recall","distraction","meld"},
	ALIGN_NEUTRAL,	true	},
    {	"cthon",	"Cthon",	{"recall","fear","speed"},
	ALIGN_EVIL,	true	},
    {	"hermes",	"Hermes",	{"recall","transport"},
	ALIGN_NONE,	true	}
};
*/

/* don't forget to give these a function in give_gift() deity.c */
const struct gift_type gift_table[] =
{
    {	"recall",	75	},
    {	"random",	50	},
    {	"patience",	100	},
    {	"nurture",	100	},
    {	"meld",		100	},
    {	"reanimation",	200	},
    {	"opiate",	50	},
    {	"bravery",	100	},
    {	"stature",	100	},
    {	"distraction",	100	},
    {	"fear",		150	},
    {	"speed",	200	},
    {	"transport",	150	},
    {   "knowledge",    25      },
    {   "banishment",   200     },
    {	"",		0	}
};

/* for position */
const struct position_type position_table[] =
{
    {   "dead",                 "dead"  },
    {   "mortally wounded",     "mort"  },
    {   "incapacitated",        "incap" },
    {   "stunned",              "stun"  },
    {   "sleeping",             "sleep" },
    {   "resting",              "rest"  },
    {   "sitting",              "sit"   },
    {   "fighting",             "fight" },
    {   "standing",             "stand" },
    {   NULL,                   NULL    }
};

/* for sex */
const struct sex_type sex_table[] =
{
   {    "none"          },
   {    "male"          },
   {    "female"        },
   {    "either"        },
   {    NULL            }
};

/* for sizes */
const struct size_type size_table[] =
{ 
    {   "tiny"          },
    {   "small"         },
    {   "medium"        },
    {   "large"         },
    {   "huge"          },
    {   "giant"         },
    {   NULL            }
};

/* for obj sizes */
const struct obj_size_type obj_size_table[] =
{ 
    {   "one size fits all"  },
    {   "tiny"          },
    {   "small"         },
    {   "medium"        },
    {   "large"         },
    {   "huge"          },
    {   "giant"         },
    {   NULL            }
};

/* various flag tables */
const struct flag_type mhs_flags[] =
{
    {   "old-reclass",          A,      true    },
    {   "mutant",               B,      true    },
    {   "highlander",           C,      true    },
    {   "savant",               D,      true    },
    {   "shapeshifter",         E,      true    },
    {   "shapemorph",           F,      true    },
    {   "norescue",             G,      true    },
    {   NULL,                   0,      0       }
};

const struct flag_type act_flags[] =
{
    {   "npc",                  A,      false   },
    {   "sentinel",             B,      true    },
    {   "scavenger",            C,      true    },
    {   "aggressive",           F,      true    },
    {   "stay_area",            G,      true    },
    {   "wimpy",                H,      true    },
    {   "pet",                  I,      true    },
    {   "train",                J,      true    },
    {   "practice",             K,      true    },
    {   "undead",               O,      true    },
    {   "weaponsmith",          P,      true    },
    {   "cleric",               Q,      true    },
    {   "mage",                 R,      true    },
    {   "thief",                S,      true    },
    {   "warrior",              T,      true    },
    {   "noalign",              U,      true    },
    {   "nopurge",              V,      true    },
    {   "outdoors",             W,      true    },
    {   "armourer",             X,      true    },
    {   "indoors",              Y,      true    },
    {	"mount",		Z,	true	},
    {   "healer",               aa,     true    },
    {   "gain",                 bb,     true    },
    {   "update_always",        cc,     true    },
    {   "changer",              dd,     true    },
    {   "notrans",		ee,	true	}, 
    {   NULL,                   0,      false   }
};

const struct flag_type plr_flags[] =
{
    {   "npc",                  A,      false   },
    {   "autoassist",           C,      false   },
    {   "autoexit",             D,      false   },
    {   "autoloot",             E,      false   },
    {   "autosac",              F,      false   },
    {   "autogold",             G,      false   },
    {   "autosplit",            H,      false   },
    {   "honor",                I,      false   },
    {   "circle",               J,      false   },
    {   "demise",               K,      false   },
    {   "balance",              L,      false   },
    {   "loner",                M,      false   },
    {   "holylight",            N,      false   },
    {   "can_loot",             P,      false   },
    {   "nosummon",             Q,      false   },
    {   "nofollow",             R,      false   },
    {   "permit",               U,      true    },
    {   "dweeb",                V,      false   },
    {   "log",                  W,      false   },
    {   "deny",                 X,      false   },
    {   "freeze",               Y,      false   },
    {   "thief",                Z,      false   },
    {   "killer",               aa,     false   },
    {   "thug",                 bb,     false   },
    {   NULL,                   0,      0       }
};

const struct flag_type affect_flags[] =
{
    {   "blind",                A,      true    },
    {   "invisible",            B,      true    },
    {   "detect_evil",          C,      true    },
    {   "detect_invis",         D,      true    },
    {   "detect_magic",         E,      true    },
    {   "detect_hidden",        F,      true    },
    {   "detect_good",          G,      true    },
    {   "sanctuary",            H,      true    },
    {   "faerie_fire",          I,      true    },
    {   "infrared",             J,      true    },
    {   "curse",                K,      true    },
    {   "poison",               M,      true    },
    {   "protect_evil",         N,      true    },
    {   "protect_good",         O,      true    },
    {   "sneak",                P,      true    },
    {   "hide",                 Q,      true    },
    {   "sleep",                R,      true    },
    {   "charm",                S,      true    },
    {   "flying",               T,      true    },
    {   "pass_door",            U,      true    },
    {   "haste",                V,      true    },
    {   "calm",                 W,      true    },
    {   "plague",               X,      true    },
    {   "weaken",               Y,      true    },
    {   "dark_vision",          Z,      true    },
    {   "berserk",              aa,     true    },
    {   "swim",                 bb,     true    },
    {   "regeneration",         cc,     true    },
    {   "slow",                 dd,     true    },
    {   NULL,                   0,      0       }
};

const struct flag_type off_flags[] =
{
    {   "area_attack",          A,      true    },
    {   "backstab",             B,      true    },
    {   "bash",                 C,      true    },
    {   "berserk",              D,      true    },
    {   "disarm",               E,      true    },
    {   "dodge",                F,      true    },
    {   "fade",                 G,      true    },
    {   "fast",                 H,      true    },
    {   "kick",                 I,      true    },
    {   "dirt_kick",            J,      true    },
    {   "parry",                K,      true    },
    {   "rescue",               L,      true    },
    {   "tail",                 M,      true    },
    {   "trip",                 N,      true    },
    {   "crush",                O,      true    },
    {   "assist_all",           P,      true    },
    {   "assist_align",         Q,      true    },
    {   "assist_race",          R,      true    },
    {   "assist_players",       S,      true    },
    {   "assist_guard",         T,      true    },
    {   "assist_vnum",          U,      true    },
    {   NULL,                   0,      0       }
};

const struct flag_type imm_flags[] =
{
    {   "summon",               A,      true    },
    {   "charm",                B,      true    },
    {   "magic",                C,      true    },
    {   "weapon",               D,      true    },
    {   "bash",                 E,      true    },
    {   "pierce",               F,      true    },
    {   "slash",                G,      true    },
    {   "fire",                 H,      true    },
    {   "cold",                 I,      true    },
    {   "lightning",            J,      true    },
    {   "acid",                 K,      true    },
    {   "poison",               L,      true    },
    {   "negative",             M,      true    },
    {   "holy",                 N,      true    },
    {   "energy",               O,      true    },
    {   "mental",               P,      true    },
    {   "disease",              Q,      true    },
    {   "drowning",             R,      true    },
    {   "light",                S,      true    },
    {   "sound",                T,      true    },
    {   "wood",                 X,      true    },
    {   "silver",               Y,      true    },
    {   "iron",                 Z,      true    },
    {   NULL,                   0,      0       }
};

const struct flag_type form_flags[] =
{
    {   "edible",               FORM_EDIBLE,            true    },
    {   "poison",               FORM_POISON,            true    },
    {   "magical",              FORM_MAGICAL,           true    },
    {   "instant_decay",        FORM_INSTANT_DECAY,     true    },
    {   "other",                FORM_OTHER,             true    },
    {   "animal",               FORM_ANIMAL,            true    },
    {   "sentient",             FORM_SENTIENT,          true    },
    {   "undead",               FORM_UNDEAD,            true    },
    {   "construct",            FORM_CONSTRUCT,         true    },
    {   "mist",                 FORM_MIST,              true    },
    {   "intangible",           FORM_INTANGIBLE,        true    },
    {   "biped",                FORM_BIPED,             true    },
    {   "centaur",              FORM_CENTAUR,           true    },
    {   "insect",               FORM_INSECT,            true    },
    {   "spider",               FORM_SPIDER,            true    },
    {   "crustacean",           FORM_CRUSTACEAN,        true    },
    {   "worm",                 FORM_WORM,              true    },
    {   "blob",                 FORM_BLOB,              true    },
    {   "mammal",               FORM_MAMMAL,            true    },
    {   "bird",                 FORM_BIRD,              true    },
    {   "reptile",              FORM_REPTILE,           true    },
    {   "snake",                FORM_SNAKE,             true    },
    {   "dragon",               FORM_DRAGON,            true    },
    {   "amphibian",            FORM_AMPHIBIAN,         true    },
    {   "fish",                 FORM_FISH ,             true    },
    {   "cold_blood",           FORM_COLD_BLOOD,        true    },
    {   NULL,                   0,                      0       }
};

const struct flag_type part_flags[] =
{
    {   "head",                 PART_HEAD,              true    },
    {   "arms",                 PART_ARMS,              true    },
    {   "legs",                 PART_LEGS,              true    },
    {   "heart",                PART_HEART,             true    },
    {   "brains",               PART_BRAINS,            true    },
    {   "guts",                 PART_GUTS,              true    },
    {   "hands",                PART_HANDS,             true    },
    {   "feet",                 PART_FEET,              true    },
    {   "fingers",              PART_FINGERS,           true    },
    {   "ear",                  PART_EAR,               true    },
    {   "eye",                  PART_EYE,               true    },
    {   "long_tongue",          PART_LONG_TONGUE,       true    },
    {   "eyestalks",            PART_EYESTALKS,         true    },
    {   "tentacles",            PART_TENTACLES,         true    },
    {   "fins",                 PART_FINS,              true    },
    {   "wings",                PART_WINGS,             true    },
    {   "tail",                 PART_TAIL,              true    },
    {   "claws",                PART_CLAWS,             true    },
    {   "fangs",                PART_FANGS,             true    },
    {   "horns",                PART_HORNS,             true    },
    {   "scales",               PART_SCALES,            true    },
    {   "tusks",                PART_TUSKS,             true    },
    {   NULL,                   0,                      0       }
};

const struct flag_type disp_flags[]=
{
    {   "compact",		DISP_COMPACT,		true	},
    {   "brief_desc",		DISP_BRIEF_DESCR,	true	},
    {   "brief_combat",		DISP_BRIEF_COMBAT,	true	},
    {	"brief_wholist",	DISP_BRIEF_WHOLIST,	true	},
    {	"brief_eqlist",		DISP_BRIEF_EQLIST,	true	},
    {	"prompt",		DISP_PROMPT,		true	},
    {	"show_affected",	DISP_SHOW_AFFECTS,	true	},  
    {	"disp_vnum",		DISP_DISP_VNUM,		true	},
    {   "color",		DISP_COLOR,		true	},
    {   "combine",		DISP_COMBINE,		true    },
    {   "scan",                 DISP_BRIEF_SCAN,        true    },
    {	NULL,			0,			0	}
};

const struct flag_type comm_flags[] =
{
    {   "quiet",                COMM_QUIET,             true    },
    {   "deaf",                 COMM_DEAF,              true    },
    {   "nowiz",                COMM_NOWIZ,             true    },
    {   "nobitch",              COMM_NOBITCH,           true    },
    {   "noclangossip",         COMM_NOAUCTION,         true    },
    {   "nogossip",             COMM_NOGOSSIP,          true    },
    {	"noooc",		COMM_NOOOC,		true	},
    {   "noquestion",           COMM_NOQUESTION,        true    },
    {   "nomusic",              COMM_NOMUSIC,           true    },
    {   "noclan",               COMM_NOCLAN,            true    },
    {   "noquest",              COMM_NOQUOTE,           true    },
    /**
    {   "shoutsoff",            COMM_SHOUTSOFF,         true    },
     **/
    {   "true_trust",           COMM_true_TRUST,        true    },
    {   "telnet_ga",            COMM_TELNET_GA,         true    },
    {   "nograts",              COMM_NOGRATS,           true    },
    {   "noemote",              COMM_NOEMOTE,           false   },
    {   "noshout",              COMM_NOSHOUT,           false   },
    {   "notell",               COMM_NOTELL,            false   },
    {   "nochannels",           COMM_NOCHANNELS,        false   },
    {   "nonotes",		COMM_NONOTES,		false   },
    {   "snoop_proof",          COMM_SNOOP_PROOF,       false   },
    {   "afk",                  COMM_AFK,               true    },
    {   NULL,                   0,                      0       }
};















