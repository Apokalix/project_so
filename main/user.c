#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#include "../function_supp/support.h"
#include "../function_main/messageQueue.h"

struct Msgbuf msg;


void sendMsg(){
    msgsnd(getMessageID(),&msg,MSG_MAX_SIZE,IPC_NOWAIT);
}


int main(int argc, char *argv[]) {

    msg.mtype = 1;

    sprintf(msg.mtext, "%d %d %d %d %d",timestamp, getpid(), receiver, amount, reward);

    sendMsg();


}
