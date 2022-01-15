#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "../function_supp/support.h"
#include "../function_supp/shmFunctions.h"

int *array;

int main(int argc, char *argv[]){

    array = getSharedArray();
    /*
    for (i = 0; i < ARRAY_SIZE; i++){
        printf("%d\n", array[i]);
    }
    */

    exit(EXIT_SUCCESS);
}