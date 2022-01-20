#include "shmMasterBook.h"
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../core/keys.h"
#include "../function_supp/support.h"
#include "../core/transaction.h"

int getIDMasterBook(){
    int shm_id;

    if((shm_id = shmget(KEYMASTERBOOK, (sizeof(struct Transaction) * (SO_BLOCK_SIZE*SO_REGISTRY_SIZE)),0666 |IPC_CREAT)) <0){
        fprintf(stderr,"%s: %d. error in shmgetMASTERBOOK #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return shm_id;
}

Transaction *getSharedMasterBook(){
    Transaction *address;

    if(getIDMasterBook()==-1){
        fprintf(stderr,"%s: %d. error in shmgetMASTERBOOK #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    address= shmat(getIDMasterBook(), NULL,0);

    if(errno){
        fprintf(stderr,"%s: %d. error in shmatMASTERBOOK #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return address;
}

void clearMemoryMasterBook(){
    if((shmctl(getIDMasterBook(),IPC_RMID,0))==-1){
        fprintf(stderr,"%s: %d. error in shmctlMASTERBOOK #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}