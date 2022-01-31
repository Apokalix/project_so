#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../core/keys.h"
#include "messageQueue.h"

int getMsgID() {

    int msg_id;
    if ((msg_id = msgget(KEYMSG, IPC_CREAT | 0666)) < 0) {
        fprintf(stderr, "%s: %d. Error in msgget #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return msg_id;

}

void clearMsg() {

    if ((msgctl(getMsgID(), IPC_RMID, NULL)) == -1) {
        fprintf(stderr, "%s: %d. Errore in msgctl #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}