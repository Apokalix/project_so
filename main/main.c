#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "../function_supp/readInputFile.h"
#include "../function_supp/support.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_supp/shmMasterBook.h"
#include "../function_supp/creationBook.h"

int *array;
Transaction *book;

void signHandler(int signum){
    clearMemoryArray();
    clearMemoryMasterBook();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int result_fork;
    char **master_prm=NULL;


    book=getSharedMasterBook();
    bookInit(book);
    printBook(book);


    printf("\n");

    signal(SIGINT,signHandler);


    array = getSharedArray();
    readInputFile(array);

    result_fork = fork();
    if(result_fork==-1){
        exit(EXIT_FAILURE);
    }
    else if(result_fork == 0){
        execv("./exec/master", master_prm);
    }

    sleep(2);
    clearMemoryArray();
    clearMemoryMasterBook();

    exit(EXIT_SUCCESS);
}