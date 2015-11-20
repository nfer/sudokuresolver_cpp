
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

Sudoku::Sudoku() {
    data = new int[81];
    dataExcl = new int[81];
    dataTips = new int*[81];
    for(int i = 0; i < 81; i++)
        dataTips[i] = new int[9];
}

Sudoku::Sudoku(int *_data) {
    data = new int[81];
    dataExcl = new int[81];
    dataTips = new int*[81];
    for(int i = 0; i < 81; i++)
        dataTips[i] = new int[9];

    init(_data);
}

Sudoku::~Sudoku() {
    delete []data;
    delete []dataExcl;
    for(int i = 0; i < 81; i++)
        delete []dataTips[i];
    delete []dataTips;
}

void Sudoku::init(int *_data) {
    for (int i = 0; i < 81; i++) {
        int value = _data[i];
        data[i] = value;
        if (value != 0) {
            dataTips[i][value - 1] = value;
        } else {
            for (int j = 0; j < 9; j++) {
                dataTips[i][j] = j + 1;
            }
        }
    }
}

int Sudoku::count() const {
    int count = 0;
    for (int i = 0; i < 81; i++) {
        if (data[i] != 0) {
            count++;
        }
    }
    return count;
}

void Sudoku::outputData() const {
    printf("┌───────┬───────┬───────┐\n");

    for (int i = 0; i < 81; i++) {
        if (i % 9 == 0)
            printf("│");
        int temp = data[i];
        if (temp == 0)
            printf("  ");
        else
            printf(" %d", temp);

        if (i % 3 == 2) {
            printf(" │");
            if (i % 9 == 8 && i % 27 != 26)
                printf("\n");

            if (i % 27 == 26 && i != 81 - 1)
                printf("\n├───────┼───────┼───────┤\n");
        }
    }

    printf("\n└───────┴───────┴───────┘\n");
}

void Sudoku::outputDataTips() {
    for (int i = 0; i < 81; i++) {
        if (data[i] != 0)
            continue;

        outputBox(i, dataTips[i]);
    }
}

void Sudoku::exclusiveRange() {
    stepBox();
    stepRow();
    stepColumn();
    updateDataFromTips();
}

// =========================private functions==================================
void Sudoku::outputBox(int index, int box[]) {
    printf("┌───┬─%d─┬───┐\n", index % 9 + 1);

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            if (i % 6 != 0)
                printf("%d", index / 9 + 1);
            else
                printf("│");
        }

        int temp = box[i];
        if (temp == 0)
            printf("   ");
        else
            printf(" %d ", temp);

        if (i % 3 == 2 && i != 9 - 1) {
            printf("│");
            printf("\n├───┼───┼───┤\n");
        } else
            printf("│");
    }

    printf("\n└───┴───┴───┘\n");
}

void Sudoku::stepBox() {
    for (int i = 0; i < 81; i++) {
        int indexs[9] = {0};
        Sudoku::getBoxIndex(i, indexs);
        updateDataTips(i, indexs);
    }
}

void Sudoku::stepRow() {
    for (int i = 0; i < 81; i++) {
        int indexs[9] = {0};
        Sudoku::getRowIndex(i, indexs);
        updateDataTips(i, indexs);
    }
}

void Sudoku::stepColumn() {
    for (int i = 0; i < 81; i++) {
        int indexs[9] = {0};
        Sudoku::getColumnIndex(i, indexs);
        updateDataTips(i, indexs);
    }
}

void Sudoku::updateDataTips(int i, int * indexs) {
    if (data[i] != 0)
        return;

    for (int j = 0; j < 9; j++) {
        int index = indexs[j];
        int value = data[index];
        if (value != 0)
            dataTips[i][value - 1] = 0;
    }
}

void Sudoku::updateDataFromTips() {
    for (int i = 0; i < 81; i++) {
        if (data[i] != 0)
            continue;

        int index = Sudoku::getIndex(dataTips[i]);
        if (index != 0) {
            data[i] = index;
        }
    }
}

// =========================static functions===================================
int Sudoku::getIndex(int * tips) {
    int index = 0;
    for (int i = 0; i < 9; i++) {
        if (tips[i] != 0) {
            if (index != 0)
                return 0;

            index = tips[i];
        }

    }
    return index;
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

void Sudoku::getColumnIndex(int index, int * indexs) {
    int result[] = { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
    for (int i = 0; i < 9; i++) {
        indexs[i] = result[i] + index % 9;
    }
}
