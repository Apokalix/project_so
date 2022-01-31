
#ifndef PROJECT_SO_TRANSACTION_H
#define PROJECT_SO_TRANSACTION_H

typedef struct Transaction{
    char timestamp[20];
    char sender;
    char receiver;
    int amount;
    int reward;
}Transaction;
#endif
