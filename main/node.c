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
#include "../function_supp/suppUtility.h"

Transaction transaction_pool[SO_TP_SIZE];

Transaction transactionReward(int reward){
    Transaction t_reward;
    char supp_buff[32];


    t_reward.timestamp = ;
    t_reward.sender = ;
    itoa(getpid(), t_reward.receiver, 10);
    t_reward.amount = reward;
    t_reward.reward = 0;

}

Transaction extractionPool(Transaction supp_array[SO_BLOCK_SIZE], int placeholder_pool) {


    int count_dimsup;
    int reward;

    for (count_dimsup = 0; count_dimsup < SO_BLOCK_SIZE - 1; count_dimsup++) {

        supp_array[count_dimsup] = transaction_pool[placeholder_pool];
        reward = reward + supp_array[count_dimsup].reward;

    }
    supp_array[SO_BLOCK_SIZE-1] = transactionReward(reward);

    return supp_array;
}







int main(int argc, char *argv[]) {

}
