#ifndef PROJECT_SO_CREATIONBOOK_H
#define PROJECT_SO_CREATIONBOOK_H
#include "../core/transaction.h"

void bookInit(Transaction *book, int timestamp, int sender, int receiver, int amount, int reward);
void printBook(Transaction *book, int timestamp, int sender, int receiver, int amount, int reward);

#endif