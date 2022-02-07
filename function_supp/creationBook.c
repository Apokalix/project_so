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
#include "shmFunctions.h"

/*
void bookInit(Transaction *book, int timestamp, int sender, int receiver, int amount, int reward){
    int line,column;

    for(line = 0; line < SO_REGISTRY_SIZE; line++) {
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            book[column+(line*SO_BLOCK_SIZE)].timestamp = timestamp;
            book[column+(line*SO_BLOCK_SIZE)].sender = sender;
            book[column+(line*SO_BLOCK_SIZE)].receiver = receiver;
            book[column+(line*SO_BLOCK_SIZE)].amount = amount;
            book[column+(line*SO_BLOCK_SIZE)].reward = reward;
        }
    }
}
*/
int *supp_values;

void bookInit(Transaction *book, int timestamp, int sender, int receiver, int amount, int reward){
    supp_values = getSharedSuppValues();

    book[supp_values[COLUMN]+(supp_values[LINE]*SO_BLOCK_SIZE)].timestamp = timestamp;
    book[supp_values[COLUMN]+(supp_values[LINE]*SO_BLOCK_SIZE)].sender = sender;
    book[supp_values[COLUMN]+(supp_values[LINE]*SO_BLOCK_SIZE)].receiver = receiver;
    book[supp_values[COLUMN]+(supp_values[LINE]*SO_BLOCK_SIZE)].amount = amount;
    book[supp_values[COLUMN]+(supp_values[LINE]*SO_BLOCK_SIZE)].reward = reward;

    if(supp_values[COLUMN] == SO_BLOCK_SIZE-1){
        if(supp_values[LINE] == SO_REGISTRY_SIZE-1){
            exit(EXIT_FAILURE);
        }
        supp_values[COLUMN] = 0;
        supp_values[LINE] = supp_values[LINE]+1;
    }
    else{
        supp_values[COLUMN] = supp_values[COLUMN]+1;
    }

}

void printBook(Transaction *book, int timestamp, int sender, int receiver, int amount, int reward){
    int line,column;

    for (line = 0; line < SO_REGISTRY_SIZE; line++) {
        printf("\n");
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            printf(" sender: %d receiver: %d amount: %d reward: %d time in ns: %d \n", book[column+(line*SO_BLOCK_SIZE)].sender,book[column+(line*SO_BLOCK_SIZE)].receiver,
                   book[column+(line*SO_BLOCK_SIZE)].amount,book[column+(line*SO_BLOCK_SIZE)].reward,book[column+(line*SO_BLOCK_SIZE)].timestamp);
        }
    }
    printf("\n");
}