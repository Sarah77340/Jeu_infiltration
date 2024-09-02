# CROZAT Alex
# NGUYEN Sarah
# Makefile for Stealth Projet

CC=gcc
CFLAGS=-Wall -ansi -pedantic -O2 -lm
DIR_H = include/
DIR_C = src/
DIR_O = bin/
EXEC=stealth

all: install 

$(EXEC): $(DIR_C)$(EXEC).c geometry.o L3_random.o dynamic_array.o terrain.o display.o entity.o game.o leaderboard.o
	$(CC) -o $@ $^ $(CFLAGS) -lMLV -D_POSIX_C_SOURCE=199309L

geometry.o: $(DIR_H)geometry.h
	gcc -c $(DIR_C)geometry.c $(CFLAGS)

L3_random.o: $(DIR_H)L3_random.h
	gcc -c $(DIR_C)L3_random.c $(CFLAGS)

dynamic_array.o: $(DIR_H)dynamic_array.h $(DIR_H)geometry.h $(DIR_H)L3_random.h
	gcc -c $(DIR_C)dynamic_array.c $(CFLAGS)

terrain.o: $(DIR_H)terrain.h $(DIR_H)geometry.h $(DIR_H)L3_random.h
	gcc -c $(DIR_C)terrain.c $(CFLAGS)

entity.o: $(DIR_H)entity.h $(DIR_H)terrain.h $(DIR_H)geometry.h $(DIR_H)L3_random.h
	gcc -c $(DIR_C)entity.c $(CFLAGS)

display.o: $(DIR_H)display.h
	gcc -c $(DIR_C)display.c $(CFLAGS) -lMLV

game.o: $(DIR_H)game.h
	gcc -c $(DIR_C)game.c $(CFLAGS)

leaderboard.o: $(DIR_H)leaderboard.h
	gcc -c $(DIR_C)leaderboard.c $(CFLAGS)

install: $(EXEC) 
	mv display.o ./$(DIR_O)
	mv entity.o ./$(DIR_O)
	mv dynamic_array.o ./$(DIR_O)
	mv terrain.o ./$(DIR_O)
	mv geometry.o ./$(DIR_O)
	mv L3_random.o ./$(DIR_O)
	mv game.o ./$(DIR_O)
	mv leaderboard.o ./$(DIR_O)

clean:
	rm -f $(DIR_O)*.o