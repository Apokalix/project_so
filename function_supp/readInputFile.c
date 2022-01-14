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

        str = strtok(NULL," ");
        value = atoi(str);

        array[cont] = value;
        cont = cont + 1;

    }

    fclose(input_file);

}