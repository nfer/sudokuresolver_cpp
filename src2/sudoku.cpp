
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

static int boxIndexs[] = {0, 3,  6, 27, 30, 36, 54, 57, 60}; // (i / 3) * 27 + (i % 3) * 3
static int rowIndexs[] = {0, 9, 18, 27, 36, 45, 54, 63, 72}; // i * 9
static int colIndexs[] = {0, 1,  2,  3,  4,  5,  6,  7,  8}; // i

Sudoku::Sudoku() {
}

Sudoku::Sudoku(int *data) {
    init(data);
}

Sudoku::~Sudoku() {
}

void Sudoku::init(int *data) {
    mCount = 0;
    for (int i = 0; i < 81; i++) {
        int value = data[i];
        mData[i] = value;
        if (value != 0) {
            mCount++;
        }
    }
}

int Sudoku::valid() {
    int indexs[9] = {0};
    for (int i = 0; i < 9; i++) {
        // check box[i] valid
        Sudoku::getBoxIndex(boxIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            if ( SUDOKU_DEBUG ) printf("check box %d valid failed.\n", i);
            return Sudoku::ERR_BOX_DUPLICATE;
        }

        // check row[i] valid
        Sudoku::getRowIndex(rowIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            if ( SUDOKU_DEBUG ) printf("check row %d valid failed.\n", i);
            return Sudoku::ERR_ROW_DUPLICATE;
        }

        // check col[i] valid
        Sudoku::getColIndex(colIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            if ( SUDOKU_DEBUG ) printf("check col %d valid failed.\n", i);
            return Sudoku::ERR_COL_DUPLICATE;
        }
    }
    return Sudoku::ERR_NO_ERROR;
}

void Sudoku::outputData() {
    outputBox81(mData);
}

// =========================private functions==================================

// =========================static functions===================================
void Sudoku::outputBox81(int *box) {
    printf("   1 2 3   4 5 6   7 8 9  \n");
    printf(" ┌───────┬───────┬───────┐\n");

    for (int i = 0; i < 81; i++) {
        if (i % 9 == 0)
            printf("%d│", i / 9 + 1);
        int temp = box[i];
        if (temp == 0)
            printf("  ");
        else
            printf(" %d", temp);

        if (i % 3 == 2) {
            printf(" │");
            if (i % 9 == 8 && i % 27 != 26)
                printf("\n");

            if (i % 27 == 26 && i != 81 - 1)
                printf("\n ├───────┼───────┼───────┤\n");
        }
    }

    printf("\n └───────┴───────┴───────┘\n");
    printf("   1 2 3   4 5 6   7 8 9  \n");
}

void Sudoku::getBoxIndex(int index, int * indexs) {
    int result[] = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };
    for (int i = 0; i < 9; i++) {
        indexs[i] = result[i] + (index / 27) * 27 + index % 9 - index % 3;
    }
}

void Sudoku::getRowIndex(int index, int * indexs) {
    int result[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    for (int i = 0; i < 9; i++) {
        indexs[i] = result[i] + (index / 9) * 9;
    }
}

void Sudoku::getColIndex(int index, int * indexs) {
    int result[] = { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
    for (int i = 0; i < 9; i++) {
        indexs[i] = result[i] + index % 9;
    }
}

int Sudoku::checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type) {
    int flag[9] = {0};
    int count = 0, index = -1;

    for (int i = 0; i < 9; i++) {
        int value = data[indexs[i]];
        if (value == 0)
            continue;

        flag[value-1]++;
        count++;
        index = indexs[i];

        if (flag[value-1] > 1) {
            if ( SUDOKU_DEBUG ) {
                printf("there is duplicate(%d) number %d\n", flag[value-1], value);
            }
            return -1;
        }
    }

    switch (type) {
        case UNIQUE:
            if (count == 1)
                return index;
            else
                return -1;

        case FULL:
            if (count == 9)
                return 0;
            else
                return -1;
            break;

        case NODUP:
        default:
            break;
    }
    return 0;
}
