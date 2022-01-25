#ifndef PROJECT_SO_SEMAPHORES_H
#define PROJECT_SO_SEMAPHORES_H

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int getSemId();
int semReserve(int sem_id, int sem_num);
int semRelease(int sem_id, int sem_num);
int semRemove(int sem_id);

#endif