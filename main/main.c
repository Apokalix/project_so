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

int *array;

void signHandler(int signum){
    clearMemoryArray();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int result_fork;
    char **master_prm=NULL;
    int line,page;


    Transaction book[SO_BLOCK_SIZE][SO_REGISTRY_SIZE];

    /*
    for(page = 0; page < SO_REGISTRY_SIZE; page ++) {
        for (line = 0; line < SO_BLOCK_SIZE; line++) {
                book[line][page].timestamp = 'A';
        }
    }

        for (page = 0; page < SO_REGISTRY_SIZE; page++) {
        printf("\n");
        for (line = 0; line < SO_BLOCK_SIZE; line++) {
            printf(" %c", book[line][page].timestamp);
        }
    }
    printf("\n");
    */

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

    exit(EXIT_SUCCESS);
}