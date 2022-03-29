#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
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
int *array;
Transaction *book;
int placeholder_pool, placeholder_extraction;
Transaction supp_array[SO_BLOCK_SIZE];

void receiveMsg(Transaction *transaction_pool, int i){
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

Transaction extractionPool(Transaction *transaction_pool) {

    int count_dimsup;
    int t_reward;

    for (count_dimsup = 0; count_dimsup < SO_BLOCK_SIZE - 1; count_dimsup++){

        supp_array[count_dimsup] = transaction_pool[placeholder_extraction];
        t_reward = t_reward + supp_array[count_dimsup].reward;

    }
    supp_array[SO_BLOCK_SIZE-1] = transactionReward(t_reward);
    placeholder_extraction = count_dimsup;
    return *supp_array;
}

void populationPool(Transaction *transaction_pool){
    int i;
    i = placeholder_pool;

    for(i; i < array[SO_TP_SIZE]; i++){
      receiveMsg(transaction_pool, i);
    }
    if(i == array[SO_TP_SIZE]){
        /* msg_error */
    }

    placeholder_pool = i;
}

void compilationBook(Transaction *extracted_array){
    int i;
    for(i = 0; i < SO_BLOCK_SIZE; i++){
        bookInit(book,extracted_array[i].timestamp,extracted_array[i].sender,extracted_array[i].receiver,
                 extracted_array[i].amount,extracted_array[i].reward);
    }
}

int main(int argc, char *argv[]) {

    array=getSharedArray();

    Transaction transaction_pool[array[SO_TP_SIZE]];

    placeholder_pool = 0;
    placeholder_extraction = 0;

    book=getSharedMasterBook();
    while(placeholder_pool < array[SO_TP_SIZE]){
        populationPool(transaction_pool);
    }
    extractionPool(transaction_pool);

    compilationBook(supp_array);

    shmdt(array);
    exit(EXIT_SUCCESS);
}