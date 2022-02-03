
#ifndef PROJECT_SO_TRANSACTION_H
#define PROJECT_SO_TRANSACTION_H

typedef struct Transaction{
    int timestamp;
    int sender;
    int receiver;
    int amount;
    int reward;
}Transaction;
#endif
