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
int timestamp;
char sender;
char receiver;
int import;
int reward;

int main(int argc, char *argv[]){

    array = getSharedArray();
    book=getSharedMasterBook();
    array = getSharedArray();




    clearMsg();
    shmdt(array);
    shmdt(book);

    exit(EXIT_SUCCESS);
}