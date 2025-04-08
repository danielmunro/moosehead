CC      = gcc
PROF    = -O2 -ggdb
OLC	= -DGAME_VERSION -DROM
GAME_FLAGS = -DLOG_FAILED_BOOT=0 -DLOG_LEVEL=1
C_FLAGS =  -Dmoose -Wall -Werror $(PROF) $(OLC) $(GAME_FLAGS) -I/usr/local/include
L_FLAGS =  -lm -lcrypt -lpthread -ldl -latomic_ops -lgc

O_FILES = act_comm.o act_enter.o act_info.o act_move.o act_obj.o\
	  act_wiz.o alias.o ban.o comm.o const.o db.o db2.o dns.o\
	  db3.o deity.o dump_obj_csv.o editor.o effects.o fight.o flags.o\
	  gladiator.o handler.o healer.o ident.o input.o interp.o log.o lookup.o macro.o\
	  mag2.o magic.o menu.o note.o olc.o recycle.o remort.o\
	  save.o scan.o skills.o special.o tables.o trade.o update.o \
	  live_edit.o clan.o main.o

moose: $(O_FILES)
	rm -f moose
	$(CC) -o moose $(O_FILES) $(L_FLAGS)

.c.o: merc.h
	$(CC) -c $(C_FLAGS) $<
