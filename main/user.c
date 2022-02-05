#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "../function_supp/support.h"
#include "../function_main/messageQueue.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_main/shmMasterBook.h"

struct Msgbuf msg;
Transaction *book;

void sendMsg(){
    msgsnd(getMessageID(),&msg,MSG_MAX_SIZE,IPC_NOWAIT);
}

int budgetCalculation(int budget){
    int line,column;

    for(line = 0; line < SO_REGISTRY_SIZE; line++){
        for(column = 0; column < SO_BLOCK_SIZE; column++){

            if(book[column+(line*SO_BLOCK_SIZE)].sender == getpid()){
                budget = budget - book[column+(line*SO_BLOCK_SIZE)].amount;
            }
            else if(book[column+(line*SO_BLOCK_SIZE)].receiver == getpid()){
                budget = budget + book[column+(line*SO_BLOCK_SIZE)].amount;
            }
        }
    }
    return budget;
}



int main(int argc, char *argv[]) {
    int budget;
    int *array;

    array = getSharedArray();
    book = getSharedMasterBook();

    budget = array[SO_BUDGET_INIT];
    while(1){
       budget = budgetCalculation(budget);
    }

    msg.mtype = 1;
    sprintf(msg.mtext, "%d %d %d %d %d",timestamp, getpid(), receiver, amount, reward);
    sendMsg();



    shmdt(array);
    shmdt(book);
    exit(EXIT_SUCCESS);
}
