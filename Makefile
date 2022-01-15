CC=gcc
CFLAGS=-std=c89 -pedantic -Wall

all:
	$(CC) $(CFLAGS) -c function_supp/readInputFile.c -o obj/readInputFile.o
	$(CC) $(CFLAGS) -c function_supp/shmFunctions.c -o obj/shmFunctions.o
	$(CC) $(CFLAGS) main/main.c obj/readInputFile.o obj/shmFunctions.o -o exec/main
	$(CC) $(CFLAGS) main/master.c obj/shmFunctions.o -o exec/master

again:
	rm -rf obj/*.o
	rm -rf exec/*
