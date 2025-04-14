CC = gcc

# add to C_FLAGS for profiling
PROF = -ggdb

# report all warnings, treat them as errors
WARNINGS = -Wall -Werror

# either GAME_VERSION or OLC_VERSION
VERSION = -DGAME_VERSION

# log behavior
LOGS = -DLOG_FAILED_BOOT=0 -DLOG_LEVEL=1

# include dirs for libraries
INCLUDE = -I/usr/local/include

# how much optimization gcc performs
OPTIMIZATION_LEVEL = -O2

C_FLAGS =  -Dmoose $(OPTIMIZATION_LEVEL) $(WARNINGS) $(VERSION) $(LOGS) $(INCLUDE)
L_FLAGS =  -lm -lcrypt -lpthread -ldl -latomic_ops -ljansson -lgc

O_FILES = act_comm.o act_enter.o act_info.o act_move.o act_obj.o\
	  act_wiz.o alias.o ban.o clan.o comm.o const.o db.o\
	  db2.o dns.o db3.o deity.o dump_obj_csv.o editor.o effects.o\
	  fight.o flags.o gladiator.o handler.o healer.o http.o ident.o\
	  input.o interp.o live_edit.o log.o lookup.o macro.o mag2.o\
	  magic.o main.o menu.o note.o olc.o recycle.o remort.o save.o\
	  scan.o skills.o special.o tables.o trade.o update.o

moose: $(O_FILES)
	rm -f moose
	$(CC) -o moose $(O_FILES) $(L_FLAGS)

.c.o: merc.h
	$(CC) -c $(C_FLAGS) $<
