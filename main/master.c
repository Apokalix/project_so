#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "../function_supp/support.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_supp/shmMasterBook.h"
#include "../function_supp/creationBook.h"

int *array;
Transaction *book;

int main(int argc, char *argv[]){

    array = getSharedArray();
    book=getSharedMasterBook();
    printf("SONO NEL MASTER BITCH");

    /*
    for (i = 0; i < ARRAY_SIZE; i++){
        printf("%d\n", array[i]);
    }
    */
    clearMemoryArray();
    clearMemoryMasterBook();
    exit(EXIT_SUCCESS);
}