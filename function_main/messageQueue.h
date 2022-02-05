#ifndef PROJECT_SO_MESSAGEQUEUE_H
#define PROJECT_SO_MESSAGEQUEUE_H

#define MSG_MAX_SIZE 240

struct Msgbuf{
    long mtype;
    char mtext[MSG_MAX_SIZE];
};

int getMessageID();
void clearMsg();

#endif