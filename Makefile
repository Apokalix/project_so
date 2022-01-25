CC=gcc
CFLAGS=-std=c89 -pedantic -Wall

all:
	$(CC) $(CFLAGS) -c function_supp/readInputFile.c -o obj/readInputFile.o
	$(CC) $(CFLAGS) -c function_supp/shmFunctions.c -o obj/shmFunctions.o
	$(CC) $(CFLAGS) -c function_main/shmMasterBook.c -o obj/shmMasterBook.o
	$(CC) $(CFLAGS) -c function_supp/suppUtility.c -o obj/suppUtility.o
	$(CC) $(CFLAGS) -c function_supp/creationBook.c -o obj/creationBook.o
	$(CC) $(CFLAGS) main/main.c obj/readInputFile.o obj/shmFunctions.o obj/shmMasterBook.o obj/suppUtility.o obj/creationBook.o -o exec/main
	$(CC) $(CFLAGS) main/master.c obj/shmFunctions.o obj/shmMasterBook.o obj/creationBook.o obj/readInputFile.o	-o exec/master


again:
	rm -rf obj/*.o
	rm -rf exec/*
