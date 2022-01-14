CC=gcc
CFLAGS=-std=c89 -pedantic -Wall

all:
	$(CC) $(CFLAGS) -c function_supp/readInputFile.c -o obj/readInputFile.o
	$(CC) $(CFLAGS) main/main.c obj/readInputFile.o -o exec/main
	$(CC) $(CFLAGS) main/master.c -o exec/master

again:
	rm -rf obj/*.o
	rm -rf exec/*
