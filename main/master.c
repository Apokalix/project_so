#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include "../function_supp/support.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_main/shmMasterBook.h"
#include "../function_supp/creationBook.h"
#include "../function_supp/readInputFile.h"
#include "../function_main/messageQueue.h"

int *array;
Transaction *book;
char **son_prm = NULL;
int *supp_values;

void sigTimeOutHandler(int signum){
    supp_values[TIME_SIMULATION] = 0;
}

void nodeGeneration(){
    int result_fork;

    result_fork = fork();
    if(result_fork == -1){
        exit(EXIT_FAILURE);
    }
    else if(result_fork == 0){
        execv("./exec/node", son_prm);
    }

}

int main(int argc, char *argv[]){
    int result_fork;

    array = getSharedArray();
    book=getSharedMasterBook();
    array = getSharedArray();
    supp_values = getSharedSuppValues();

    signal(SIGALRM, sigTimeOutHandler);
    alarm(array[SO_SIM_SEC]);

    supp_values[LINE] = 0;
    supp_values[COLUMN] = 0;
    result_fork = fork();
    if(result_fork == -1){
        exit(EXIT_FAILURE);
    }
    else if (result_fork == 0){
        execv("./exec/user", son_prm);
    }

    while(supp_values[TIME_SIMULATION]){
        nodeGeneration();
    }

    clearMsg();
    shmdt(array);
    shmdt(book);
    shmdt(supp_values);

    exit(EXIT_SUCCESS);
}