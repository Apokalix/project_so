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

void bookInit(Transaction *book){
    int line,column;
    int c = 1;

    for(line = 0; line < SO_REGISTRY_SIZE; line ++) {
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            book[column+(line*SO_BLOCK_SIZE)].timestamp = c ;
            book[column+(line*SO_BLOCK_SIZE)].sender = 'A';
            c++;
        }
    }

}

void printBook(Transaction *book){
    int line,column;

    for (line = 0; line < SO_REGISTRY_SIZE; line++) {
        printf("\n");
        for (column = 0; column < SO_BLOCK_SIZE; column++) {
            printf(" %d \n %c ", book[column+(line*SO_BLOCK_SIZE)].timestamp,book[column+(line*SO_BLOCK_SIZE)].sender);
        }
    }
    printf("\n");
}