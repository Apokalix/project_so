#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "../function_main/shmMasterBook.h"
#include "../function_supp/creationBook.h"
#include "../function_supp/nodeUtility.h"
#include "../function_main/messageQueue.h"
#include "../function_supp/nodeUtility.h"

struct Msgbuf msg;
Transaction *book;
Transaction transaction_pool[SO_TP_SIZE];
int placeholder_pool;

void receiveMsg(int i){
    char *str;
    int timestamp,sender,receiver,amount,reward;

    msgrcv(getMessageID(),&msg,MSG_MAX_SIZE,0,0);
    str = strtok(msg.mtext, " ");
    timestamp = atoi(str);
    str = strtok(msg.mtext, " ");
    sender = atoi(str);
    str = strtok(msg.mtext, " ");
    receiver = atoi(str);
    str = strtok(msg.mtext, " ");
    amount = atoi(str);
    str = strtok(NULL, " ");
    reward = atoi(str);

    transaction_pool[i].timestamp = timestamp;
    transaction_pool[i].sender = sender;
    transaction_pool[i].receiver = receiver;
    transaction_pool[i].amount = amount;
    transaction_pool[i].reward = reward;

}

Transaction extractionPool() {

    Transaction supp_array[SO_BLOCK_SIZE];
    int count_dimsup;
    int t_reward;

    for (count_dimsup = 0; count_dimsup < SO_BLOCK_SIZE - 1; count_dimsup++){

        supp_array[count_dimsup] = transaction_pool[placeholder_pool];
        t_reward = t_reward + supp_array[count_dimsup].reward;

    }
    supp_array[SO_BLOCK_SIZE-1] = transactionReward(t_reward);

    return *supp_array;
}

void populationPool(){
    int i;
    i = placeholder_pool;

    for(i = 0; i < SO_TP_SIZE; i++){
      receiveMsg(i);
    }
    if(i == SO_TP_SIZE){
        /* msg_error */
    }

    placeholder_pool = i;
}






int main(int argc, char *argv[]) {

    placeholder_pool = 0;

    book=getSharedMasterBook();
    compilationBook(extractionPool());

}

void compilationBook(Transaction supp_array){

    bookInit(book,timestamp,sender,receiver,amount,reward);

}