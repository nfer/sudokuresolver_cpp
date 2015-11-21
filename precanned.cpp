
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "precanned.h"

Precanned::Precanned() {
}

Precanned::~Precanned() {
}

// =========================static functions===================================
bool Precanned::parse(int argc, char * argv[], int * data) {
    if (argc == 1)
        return true;

    char * fileName = argv[argc-1];

    FILE * fd = fopen(fileName, "r");
    if (NULL == fd) {
        printf("open file %s failed\n", fileName);
        return false;
    }

    int count = 0;
    char line[32] = {'\0'};
    while(fgets(line, sizeof(line), fd)) {
        if (!parseLine(line, count, data)) {
            printf("parse line %s failed\n", line);
            return false;
        }

        count++;

        if (count == 9)
            break;
    }

    fclose(fd);
    return true;
}

bool Precanned::parseLine(char * line, int row, int * data) {
    int i = 0;
    int col = 0;
    while (line[i] && col < 9) {
        char temp = line[i];
        if (temp == ',' || temp == '\r' || temp == '\n') {
            data[row * 9 + col] = 0;
        }
        else {
            data[row * 9 + col] = temp-'0';
            i++;
        }
        col++;
        i++;
    }
    return true;
}
