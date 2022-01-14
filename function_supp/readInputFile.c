#define  _GNU_SOURCE

#include "readInputFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readInputFile(int array[]) {
    int cont;
    char *line = NULL;
    char *str;
    int value;
    size_t size = 0;
    FILE *input_file;
    input_file = fopen("inputFile1.txt", "r");
    cont = 0;
    while (getline(&line, &size, input_file) != -1) {
        str = strtok(line, " ");
        /*
        printf("%s\n", str);
        */
        str = strtok(NULL," ");
        value = atoi(str);
        /*
        printf("value: %d\n" , value);
        */
        array[cont] = value;
        cont = cont + 1;
        /*
        array[cont++] = value;
        */
    }
    fclose(input_file);
}