#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include "../function_supp/readInputFile.h"
#include "../function_supp/support.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_main/shmMasterBook.h"
#include "../function_supp/creationBook.h"

int *array;
Transaction *book;
int *supp_values;

void signHandler(int signum){
    shmdt(array);
    shmdt(book);
    clearMemoryArray();
    clearMemoryMasterBook();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int result_fork;
    char **master_prm=NULL;

    book=getSharedMasterBook();

    signal(SIGINT,signHandler);

    array = getSharedArray();
    readInputFile(array);

    supp_values = getSharedSuppValues();
    supp_values[TIME_SIMULATION] = array[SO_SIM_SEC];

    result_fork = fork();
    if(result_fork==-1){
        exit(EXIT_FAILURE);
    }
    else if(result_fork == 0){
        execv("./exec/master", master_prm);
    }
    else{
        wait(NULL);
    }

    sleep(2);

    shmdt(array);
    shmdt(book);
    shmdt(supp_values);
    clearMemoryArray();
    clearMemoryMasterBook();
    clearMemorySuppValues();

    exit(EXIT_SUCCESS);
}