#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("\n");
    printf("hello world");

    exit(EXIT_SUCCESS);
}