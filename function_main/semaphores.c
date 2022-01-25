#include "semaphores.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int getSemId(){
    int sem_id;
    if((sem_id = semget(IPC_PRIVATE, 1 , 0600)) == -1){
        fprintf(stderr,"%s: %d. Error in semget #%03d: %s \n", __FILE__, __LINE__, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return sem_id;
}

int semReserve(int sem_id, int sem_num){
    struct sembuf sops;

    sops.sem_num = sem_num;
    sops.sem_op = -1;
    sops.sem_flg = 0;

    return semop(sem_id, &sops, 1);
}

int semRelease(int sem_id, int sem_num){
    struct sembuf sops;

    sops.sem_num = sem_num;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    return semop(sem_id, &sops, 1);
}

int semRemove(int sem_id){
    return semctl(sem_id, 0, IPC_RMID);
}