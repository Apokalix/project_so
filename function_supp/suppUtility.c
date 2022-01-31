#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "suppUtility.h"
#include "../core/transaction.h"

void swap(char *x, char *y){
    char t = *x;
    *x = *y;
    *y = t;
}

char* reverse(char *buffer, int i, int j){
    while (i < j){
        swap(&buffer[i++], &buffer[j--]);
    }
    return buffer;
}

char* itoa(int value, char* buffer, int base){
    if (base < 2 || base > 32){
        return buffer;
    }

    int n = abs(value);

    int i = 0;
    while(n){
        int r = n % base;

        if(r >= 10){
            buffer[i++] = 65 + (r -10);
        }
        else{
            buffer[i++] = 48 + r;
        }
         n = n / base;
    }

    if (i == 0){
        buffer[i++] = '0';
    }

    if(value < 0 && base == 10){
        buffer[i++]= '-';
    }

    buffer[i] = '\0';
    return reverse(buffer,0,i-1);
}

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