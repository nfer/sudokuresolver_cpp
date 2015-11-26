
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

static int boxIndexs[] = {0, 3,  6, 27, 30, 36, 54, 57, 60}; // (i / 3) * 27 + (i % 3) * 3
static int rowIndexs[] = {0, 9, 18, 27, 36, 45, 54, 63, 72}; // i * 9
static int colIndexs[] = {0, 1,  2,  3,  4,  5,  6,  7,  8}; // i

Sudoku::Sudoku() {
    mData = new int[81];
    mTips = new int*[81];
    for(int i = 0; i < 81; i++)
        mTips[i] = new int[9];
}

Sudoku::Sudoku(int *data) {
    mData = new int[81];
    mTips = new int*[81];
    for(int i = 0; i < 81; i++)
        mTips[i] = new int[9];

    init(data);
}

Sudoku::~Sudoku() {
    delete []mData;
    for(int i = 0; i < 81; i++)
        delete []mTips[i];
    delete []mTips;
}

void Sudoku::init(int *data) {
    for (int i = 0; i < 81; i++) {
        int value = data[i];
        mData[i] = value;
        if (value != 0) {
            mTips[i][value - 1] = value;
        } else {
            for (int j = 0; j < 9; j++) {
                mTips[i][j] = j + 1;
            }
        }
    }
}

bool Sudoku::valid() {
    int indexs[9] = {0};
    for (int i = 0; i < 9; i++) {
        // check box[i] valid
        Sudoku::getBoxIndex(boxIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            printf("check box %d valid failed.\n", i);
            return false;
        }

        // check row[i] valid
        Sudoku::getRowIndex(rowIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            printf("check row %d valid failed.\n", i);
            return false;
        }

        // check col[i] valid
        Sudoku::getColumnIndex(colIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            printf("check col %d valid failed.\n", i);
            return false;
        }
    }
    return true;
}

int Sudoku::count() const {
    int count = 0;
    for (int i = 0; i < 81; i++) {
        if (mData[i] != 0) {
            count++;
        }
    }
    return count;
}

void Sudoku::outputData() {
    outputBox81(mData);
}

void Sudoku::outputDataTips() {
    for (int i = 0; i < 81; i++) {
        if (mData[i] != 0)
            continue;

        outputBox9(i, mTips[i]);
    }
}

bool Sudoku::exclusiveRange() {
    bool found = false;
    for (int i = 0; i < 81; i++) {
        if (mData[i] != 0)
            continue;

        int value = stepIndex(i);
        if (value != 0) {
            found = true;
            outputDataStep(value, i, "exclusiveRange");
        }
    }
    return found;
}

bool Sudoku::exclusiveNumber() {
    bool found = false;
    for (int i = 0; i < 9; i++) {
        int count = 0;
        do {
            count = stepNumber(i+1);
            if (count > 0) {
                found = true;
            }
        } while (count > 0);
    }
    // stepNumber(2);
    return found;
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

    removeTipsWithDataIndexs(tips, mData, indexsBox, 9);
    removeTipsWithDataIndexs(tips, mData, indexsRow, 9);
    removeTipsWithDataIndexs(tips, mData, indexsCol, 9);

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

    mData[index] = value;
    return value;
}

int Sudoku::stepNumber(int num) {
    int tips[81] = {0};

    for (int i = 0; i < 81; i++) {
        int value = mData[i];

        if (value == num) {
            int indexs[9] = {0};
            Sudoku::getBoxIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
            Sudoku::getRowIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
            Sudoku::getColumnIndex(i, indexs);
            setBox(tips, indexs, 9, 1);
        }
        else if (value != 0) {
            tips[i] = value;
        }
    }

    for (int i = 0; i < 81; i++) {
        int value = tips[i];
        if (value == 0)
            tips[i] = num;
        else
            tips[i] = 0;
    }

    int count = 0;
    for (int i = 0; i < 9; i++) {
        int indexs[9] = {0};
        int index = 0;

        // get box unique index
        Sudoku::getBoxIndex(boxIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != 0 && mData[index] == 0) {
            mData[index] = num;
            count++;
            outputDataStep(num, index, "exclusiveNumber by box");
        }

        // get row unique index
        Sudoku::getRowIndex(rowIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != 0 && mData[index] == 0) {
            mData[index] = num;
            count++;
            outputDataStep(num, index, "exclusiveNumber by row");
        }

        // get col unique index
        Sudoku::getColumnIndex(colIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != 0 && mData[index] == 0) {
            mData[index] = num;
            count++;
            outputDataStep(num, index, "exclusiveNumber by col");
        }
    }

    return count;
}

void Sudoku::updateDataTips(int i, int * indexs) {
    if (mData[i] != 0)
        return;

    for (int j = 0; j < 9; j++) {
        int index = indexs[j];
        int value = mData[index];
        if (value != 0)
            mTips[i][value - 1] = 0;
    }
}

void Sudoku::updateDataFromTips() {
    for (int i = 0; i < 81; i++) {
        if (mData[i] != 0)
            continue;

        int index = Sudoku::getIndex(mTips[i]);
        if (index != 0) {
            mData[i] = index;
        }
    }
}

void Sudoku::outputDataStep(int num, int index, const char * stepName) {
#ifdef DEBUG
    printf("get number %d at %d:%d with %s\n",
                num, index / 9 + 1, index % 9 + 1, stepName);
    outputData();
    printf("data count:%d\n", count());
    printf("================================================================\n\n");
#endif
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
    printf("   1 2 3   4 5 6   7 8 9  \n");
    printf(" ┌───────┬───────┬───────┐\n");

    for (int i = 0; i < 81; i++) {
        if (i % 9 == 0)
            printf("%d|", i / 9 + 1);
        int temp = box[i];
        if (temp == 0)
            printf("  ");
        else
            printf(" %d", temp);

        if (i % 3 == 2) {
            printf(" |");
            if (i % 9 == 8 && i % 27 != 26)
                printf("\n");

            if (i % 27 == 26 && i != 81 - 1)
                printf("\n ├───────┼───────┼───────┤\n");
        }
    }

    printf("\n └───────┴───────┴───────┘\n");
    printf("   1 2 3   4 5 6   7 8 9  \n");
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
    int value = -1;

    for (int i = 0; i < 9; i++) {
        int index = boxIndexs[i];
        // get one not-none item, we sign it;        
        if (box81[index] != 0) {
            // if there's more not-none items, just return 0
            if (value != -1)
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

int Sudoku::checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type) {
    int flag[9] = {0};
    int box[9] = {0};
    int count = 0, index = -1;
            // outputBox9(0, box);
            // outputBox9(0, flag);

    for (int i = 0; i < 9; i++) {
        int value = data[indexs[i]];
        box[i] = value;
        if (value != 0) {
            flag[value-1]++;
            count++;
            index = indexs[i];
        }

        if (flag[value-1] > 1) {
            printf("there is duplicate number %d\n", value);
            outputBox9(0, box);
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
