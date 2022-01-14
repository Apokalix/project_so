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

int *array;

void signHandler(int signum){
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int result_fork;
    char **master_prm=NULL;
    int i;

    signal(SIGINT,signHandler);

   /* array = getSharedArray();
    */
    readInputFile(array);
    for(i = 0; i < ARRAY_SIZE -1 ; i = i + 1)
    {
        printf("%d\n",array[i]);
    }

    result_fork = fork();
    if(result_fork==-1){
        exit(EXIT_FAILURE);
    }
    else if(result_fork == 0){
        execv("./exec/master", master_prm);
    }


    sleep(2);

    exit(EXIT_SUCCESS);
}