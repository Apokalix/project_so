#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../core/keys.h"
#include "support.h"
#include "shmFunctions.h"


int getIDArray(){
    int shm_id;

    if((shm_id = shmget(KEYARRAY,(sizeof(int) * ARRAY_SIZE),0666 |IPC_CREAT)) <0){
        fprintf(stderr,"%s: %d. error in shmgetARRAY #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return shm_id;
}

int *getSharedArray(){
    int *address;

    if(getIDArray()==-1){
        fprintf(stderr,"%s: %d. error in shmgetARRAY #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    address=shmat(getIDArray(), NULL, 0);
    if(errno){
        fprintf(stderr,"%s: %d. error in shmatARRAY #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return address;
}

void clearMemoryArray(){
    if((shmctl(getIDArray(),IPC_RMID,0))==-1){
        fprintf(stderr,"%s: %d. error in shmctlARRAY #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}