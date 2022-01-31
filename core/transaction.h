
#ifndef PROJECT_SO_TRANSACTION_H
#define PROJECT_SO_TRANSACTION_H

typedef struct Transaction{
    char timestamp[20];
    char sender[32];
    char receiver[32];
    int amount;
    int reward;
}Transaction;
#endif
