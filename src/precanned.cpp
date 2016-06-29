
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "precanned.h"

Precanned::Precanned() {
}

Precanned::~Precanned() {
}

// =========================static functions===================================
bool Precanned::parseSudokuFile(char * fileName, int * data) {
    FILE * fd = fopen(fileName, "r");
    if (NULL == fd) {
        printf("open file %s failed\n", fileName);
        return false;
    }

    int row = 0;
    char line[32] = {'\0'};
    while(fgets(line, sizeof(line), fd)) {
        if (!parseLine(line, row, data)) {
            printf("parse line %s failed\n", line);
            fclose(fd);
            return false;
        }

        row++;

        if (row == 9)
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
