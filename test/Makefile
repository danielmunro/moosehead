CC      = gcc
PROF    = -O2 -ggdb
OLC	= -DGAME_VERSION -DLOG_FAILED_BOOT=0 -DROM
C_FLAGS =  -Dmoose -Wall $(PROF) $(OLC) -I/usr/local/include
L_FLAGS =  -lm -lcrypt -lpthread -ldl -latomic_ops -lgc -ltap

O_FILES = ../src/act_comm.o ../src/act_enter.o ../src/act_info.o ../src/act_move.o ../src/act_obj.o\
		  ../src/act_wiz.o ../src/alias.o ../src/ban.o ../src/comm.o ../src/const.o ../src/db.o ../src/db2.o ../src/dns.o\
		  ../src/db3.o ../src/deity.o ../src/dump_obj_csv.o ../src/editor.o ../src/effects.o ../src/fight.o ../src/flags.o\
		  ../src/gladiator.o ../src/handler.o ../src/healer.o ../src/ident.o ../src/input.o ../src/interp.o ../src/log.o ../src/lookup.o ../src/macro.o\
		  ../src/mag2.o ../src/magic.o ../src/menu.o ../src/note.o ../src/olc.o ../src/recycle.o ../src/remort.o\
		  ../src/save.o ../src/scan.o ../src/skills.o ../src/special.o ../src/tables.o ../src/trade.o ../src/update.o \
		  ../src/live_edit.o ../src/clan.o main.o

moose: $(O_FILES)
	rm -f test
	$(CC) -o test $(O_FILES) $(L_FLAGS)

.c.o: merc.h
	$(CC) -c $(C_FLAGS) $<
