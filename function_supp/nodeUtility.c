#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "nodeUtility.h"

#define SENDER -1

Transaction transactionReward(int t_reward){
    Transaction calc_t_reward;
    char supp_buff[32];

    calc_t_reward.timestamp = 0;
    calc_t_reward.sender = SENDER;
    calc_t_reward.receiver = getpid();
    calc_t_reward.amount = t_reward;
    calc_t_reward.reward = 0;

    return calc_t_reward;

}



