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

Transaction masterBook[SO_REGISTRY_SIZE][SO_BLOCK_SIZE];

void bookInit(Transaction *book){
    int i = 0;
    int j = 0;
    int c = 1;



    for(i = 0; i < SO_REGISTRY_SIZE; i ++) {
        for (j = 0; j < SO_BLOCK_SIZE; j++) {
            masterBook[i][j].timestamp = c;
            c++;
        }
    }
    book = &masterBook[SO_REGISTRY_SIZE][SO_BLOCK_SIZE];


}

void printBook(Transaction *book){
    int i = 0;
    int j = 0;

    book = &masterBook[SO_REGISTRY_SIZE][SO_BLOCK_SIZE];

    for (i = 0; i < SO_REGISTRY_SIZE; i++) {
        printf("\n");
        for (j = 0; j < SO_BLOCK_SIZE; j++) {
            printf(" %d", masterBook[i][j].timestamp);
        }
    }
}