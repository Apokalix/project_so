#include <stdio.h>
#include <time.h>
#include "suppUtility.h"
#include "../core/transaction.h"

/*
void arrayTimestamp(char timestamp){
    time_t t;
    struct timespec spec;
    struct tm* time;

    clock_gettime(CLOCK_REALTIME, &spec);
    t = spec.tv_nsec;
    time = localtime(&spec.tv_sec);

    printf("%d-%d-%d %d:%d:%d", time->tm_year, time->tm_mon, time->tm_mday, time->tm_hour,time->tm_min, time->tm_sec);

}
*/