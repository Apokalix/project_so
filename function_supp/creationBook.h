#ifndef PROJECT_SO_CREATIONBOOK_H
#define PROJECT_SO_CREATIONBOOK_H
#include "../core/transaction.h"

void bookInit(Transaction *book, char timestamp[], char sender, char receiver, int import, int reward);
void printBook(Transaction *book, char timestamp[], char sender, char receiver, int import, int reward);

#endif