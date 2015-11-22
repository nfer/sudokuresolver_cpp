
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

void Sudoku::outputData() {
    outputBox81(data);
}

void Sudoku::outputDataTips() {
    for (int i = 0; i < 81; i++) {
        if (data[i] != 0)
            continue;

        outputBox9(i, dataTips[i]);
    }
}

void Sudoku::exclusiveRange() {
    for (int i = 0; i < 81; i++) {
        if (data[i] != 0)
            continue;

        int value = stepIndex(i);
        if (value != 0) {
            printf("get value %d at %d:%d with exclusiveRange\n",
                value, i / 9 + 1, i % 9 + 1);
        }
    }
}

void Sudoku::exclusiveNumber() {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        do {
            count = stepNumber(i+1);
            // if (count > 0)
            //     printf("exclusiveNumber exclusive %d items on number %d\n", count, i+1);
        } while (count > 0);
    }
    // stepNumber(2);
}

// =========================private functions==================================
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

int Sudoku::stepIndex(int index) {
    int indexsBox[9] = {0}, indexsRow[9] = {0}, indexsCol[9] = {0};
    int tips[9] = {1,2,3,4,5,6,7,8,9};

    Sudoku::getBoxIndex(index, indexsBox);
    Sudoku::getRowIndex(index, indexsRow);
    Sudoku::getColumnIndex(index, indexsCol);

    removeTipsWithDataIndexs(tips, data, indexsBox, 9);
    removeTipsWithDataIndexs(tips, data, indexsRow, 9);
    removeTipsWithDataIndexs(tips, data, indexsCol, 9);

    // check tips array after removed by box/row/col
    int value = 0;
    for (int i = 0; i < 9; i++) {
        if (tips[i] != 0) {
            if (value != 0) {
                return 0;
            }

            value = tips[i];
        }
    }

    data[index] = value;
    return value;
}

int Sudoku::stepNumber(int num) {
    int tips[81] = {0};
    for (int i = 0; i < 81; i++) {
        int value = data[i];

        if (value == num) {
            int indexs[9] = {0};
            Sudoku::getBoxIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
            Sudoku::getRowIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
            Sudoku::getColumnIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
        }
        else
            tips[i] |= (value != 0);
    }

    for (int i = 0; i < 81; i++) {
        int value = tips[i];
        if (value == 0)
            tips[i] = num;
        else
            tips[i] = 0;
    }
    // outputBox81(tips);

    int count = 0;
    int boxIndexs[] = {0, 3, 6, 27, 30, 36, 54, 57, 60};
    for (int i = 0; i < 9; i++) {
        int indexs[9] = {0};
        Sudoku::getBoxIndex(boxIndexs[i], indexs);
        int index = getBoxUniqueIndex(tips, indexs);
        // printf("stepNumber getBoxUniqueIndex %d at box %d\n", index, i);
        if (index != 0) {
            data[index] = num;
            count++;
        }
    }

    return count;
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
void Sudoku::removeTipsWithDataIndexs(int * tips, int *data, int * indexs, int len) {
    for (int i = 0; i < len; i++) {
        int index = indexs[i];
        int value = data[index];
        if (value != 0) {
            tips[value-1] = 0;
        }
    }
}

void Sudoku::outputBox9(int index, int box[]) {
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
        else if (temp < 10)
            printf(" %d ", temp);
        else
            printf(" %d", temp);

        if (i % 3 == 2 && i != 9 - 1) {
            printf("│");
            printf("\n├───┼───┼───┤\n");
        } else
            printf("│");
    }

    printf("\n└───┴───┴───┘\n");
}

void Sudoku::outputBox81(int *box) {
    printf("┌───────┬───────┬───────┐\n");

    for (int i = 0; i < 81; i++) {
        if (i % 9 == 0)
            printf("│");
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
                printf("\n├───────┼───────┼───────┤\n");
        }
    }

    printf("\n└───────┴───────┴───────┘\n");
}

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

// check the box whether has unique item, if has return the index
// params: box81: 9x9 data array
// params: boxIndexs: 3x3 box index array
int Sudoku::getBoxUniqueIndex(int * box81, int * boxIndexs) {
    int value = 0;

    for (int i = 0; i < 9; i++) {
        int index = boxIndexs[i];
        // get one not-none item, we sign it;        
        if (box81[index] != 0) {
            // if there's more not-none items, just return 0
            if (value != 0)
                return 0;

            value = index;
        }
    }

    return value;
}

void Sudoku::setBox(int * box, int * indexs, int len, int value) {
    int index = 0;
    for (int i = 0; i < len; i++) {
        index = indexs[i];
        box[index] = value;
    }
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
