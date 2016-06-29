
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "precanned.h"

Precanned::Precanned() {
}

Precanned::~Precanned() {
}

// =========================static functions===================================
bool Precanned::parseSudokuFile(const char * fileName, int * data) {
    FILE * fd = fopen(fileName, "r");
    if (NULL == fd) {
        return false;
    }

    int row = 0;
    char line[32] = {'\0'};
    while(fgets(line, sizeof(line), fd)) {
        if ( strlen( line ) == 0 )
            break;

        if (row > 9)
            break;

        if (!parseLine(line, row, data)) {
            fclose(fd);
            return false;
        }

        row++;
        memset(line, 0x00, sizeof(line));
    }

    fclose(fd);
    return row == 9;
}

bool Precanned::parseLine(char * line, int row, int * data) {
    int i = 0;
    int col = 0;
    while (line[i]) {
        if (col > 9)
            break;

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
    return col == 9;
}
