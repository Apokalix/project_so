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
#include "../function_main/shmMasterBook.h"
#include "../function_supp/creationBook.h"
#include "../function_supp/readInputFile.h"
#include "../function_main/messageQueue.h"

int *array;
Transaction *book;
char **son_prm = NULL;

int main(int argc, char *argv[]){
    int result_fork;

    array = getSharedArray();
    book=getSharedMasterBook();
    array = getSharedArray();

    result_fork = fork();
    if(result_fork == -1){
        exit(EXIT_FAILURE);
    }
    else if (result_fork == 0){
        execv("./exec/user", son_prm);
    }


    clearMsg();
    shmdt(array);
    shmdt(book);

    exit(EXIT_SUCCESS);
}