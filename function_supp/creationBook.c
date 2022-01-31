#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "creationBook.h"
#include "../core/transaction.h"
#include "support.h"

void bookInit(Transaction *book, char timestamp[], char sender, char receiver, int import, int reward){
    int line,column;
    int c = 1;

    for(line = 0; line < SO_REGISTRY_SIZE; line++) {
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            book[column+(line*SO_BLOCK_SIZE)].timestamp = c;
            book[column+(line*SO_BLOCK_SIZE)].sender= 'A';
            book[column+(line*SO_BLOCK_SIZE)].receiver= 'B';
            book[column+(line*SO_BLOCK_SIZE)].amount= 5;
            book[column+(line*SO_BLOCK_SIZE)].reward= 10;
            c++;
        }
    }
}

void printBook(Transaction *book, char timestamp[], char sender, char receiver, int import, int reward){
    int line,column;

    for (line = 0; line < SO_REGISTRY_SIZE; line++) {
        printf("\n");
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            printf(" sender: %c receiver: %c amount: %d reward: %d time: %s \n", book[column+(line*SO_BLOCK_SIZE)].sender,book[column+(line*SO_BLOCK_SIZE)].receiver,
                   book[column+(line*SO_BLOCK_SIZE)].amount,book[column+(line*SO_BLOCK_SIZE)].reward,book[column+(line*SO_BLOCK_SIZE)].timestamp);
        }
    }
    printf("\n");
}