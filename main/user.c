#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "../function_supp/support.h"
#include "../function_main/messageQueue.h"
#include "../function_supp/shmFunctions.h"
#include "../core/transaction.h"
#include "../function_main/shmMasterBook.h"

struct Msgbuf msg;
Transaction *book;
int *array;
int *supp_values;
struct timespec trans_time;
int num;

int rewardGen(int budget){

    int reward;
    num = (rand() % (budget - 3))+ 2;

    reward = (num*array[SO_REWARD])/100;
    if(reward >= 1){
        return reward;
    }
    else{
        reward = 1;
        return reward;
    }
}

int amountGen(int budget){
    int amount;

    amount = num - rewardGen(budget);

    return amount;
}

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
    int receiver = 1;
    array = getSharedArray();
    book = getSharedMasterBook();
    supp_values = getSharedSuppValues();

    msg.mtype = 1;

    budget = array[SO_BUDGET_INIT];
    while(supp_values[TIME_SIMULATION]){
       budget = budgetCalculation(budget);
       if(budget >= 2) {
           sprintf(msg.mtext, "%d %d %d %d %d", clock_gettime(CLOCK_REALTIME, &trans_time), getpid(), receiver,
                   amountGen(budget), rewardGen(budget));
           sendMsg();
       }
       else
       {
           exit(EXIT_FAILURE);
       }
    }






    shmdt(array);
    shmdt(book);
    exit(EXIT_SUCCESS);
}
