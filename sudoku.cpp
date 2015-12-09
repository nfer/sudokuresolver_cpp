
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
            mTips[i][value - 1] = value;
            mCount++;
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
        Sudoku::getColIndex(colIndexs[i], indexs);
        if (0 != Sudoku::checkDataWithIndexs(mData, indexs, NODUP)) {
            printf("check col %d valid failed.\n", i);
            return false;
        }
    }
    return true;
}

void Sudoku::outputData() {
    outputBox81(mData);
}

void Sudoku::outputDataTips() {
    for (int i = 0; i < 81; i++) {
        if (mData[i] != 0)
            continue;

        outputBox9(mTips[i], i);
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

    return found;
}

// =========================private functions==================================
/**
* STEP1: exclusive values at the same box/row/col
* STEP2: check whether the index has the unique value to set
*
* e.g.:  for sudoku with digits below, we want process index `25`(3,8):
* ┌───────┬───────┬───────┐
* |       |   2 3 |   1   |
* |   3   |   7   |     6 |
* |   7   | 9     |     2 |
* ├───────┼───────┼───────┤
* |   1 6 |       |   3   |
* |       | 4   9 |       |
* |   2   |       | 8 5   |
* ├───────┼───────┼───────┤
* | 1     |     8 |   7   |
* | 7     |   4   |   8   |
* |   4   | 2 5   |       |
* └───────┴───────┴───────┘
* available values: {1,2,3,4,5,6,7,8,9}
*
* STEP1: exclusive values at the same box/row/col
* ┌───────┬───────┬───────┐
* |       |   2 3 |   1   |
* |   3   |   7   |     6 |
* |   7   | 9     |   x 2 |
* ├───────┼───────┼───────┤
* |   1 6 |       |   3   |
* |       | 4   9 |       |
* |   2   |       | 8 5   |
* ├───────┼───────┼───────┤
* | 1     |     8 |   7   |
* | 7     |   4   |   8   |
* |   4   | 2 5   |       |
* └───────┴───────┴───────┘
* available values: { , ,3,4,5, ,7,8,9} // by box
* available values: { , ,3,4,5, , ,8, } // by row
* available values: { , , ,4, , , , , } // by col
*
* STEP2: check whether the index has the unique value to set
* available values: { , , ,4, , , , , }
* the unique value is 4.
*/
int Sudoku::stepIndex(int index) {
    int availables[9] = {1,2,3,4,5,6,7,8,9};

    // STEP1: exclusive values at the same box/row/col
    int indexs[9] = {0};
    getBoxIndex(index, indexs);
    removeValuesWithDataIndexs(availables, mData, indexs);
    getRowIndex(index, indexs);
    removeValuesWithDataIndexs(availables, mData, indexs);
    getColIndex(index, indexs);
    removeValuesWithDataIndexs(availables, mData, indexs);

    // STEP2: check whether the index has the unique value to set
    int value = 0;
    for (int i = 0; i < 9; i++) {
        if (availables[i] != 0) {
            if (value != 0) {
                return 0;
            }
            value = availables[i];
        }
    }

    // as not return, means we found the unique value for this index
    mCount++;
    mData[index] = value;
    outputDataStep(value, index, "exclusiveRange");
    return value;
}

/**
* STEP1: exclusive every item already has value
* STEP2: exclusive every `num` at box/row/col
* STEP3: check every box/row/col whether has the unique space to place `num`
*
* e.g.:  for sudoku with digits below, we want process number `2`:
* ┌───────┬───────┬───────┐
* | 6     | 4   8 |     9 |
* |     9 | 2 5 6 | 3     |
* |     3 |       | 2     |
* ├───────┼───────┼───────┤
* |     2 |   8   | 4     |
* |       | 9 7 5 |       |
* |       |       |       |
* ├───────┼───────┼───────┤
* |   8   | 1   7 |   2   |
* |       |       |       |
* | 7 4   |       |   8 6 |
* └───────┴───────┴───────┘
* STEP1: exclusive every item already has value
* ┌───────┬───────┬───────┐
* | x     | x   x |     x |
* |     x | 2 x x | x     |
* |     x |       | 2     |
* ├───────┼───────┼───────┤
* |     2 |   x   | x     |
* |       | x x x |       |
* |       |       |       |
* ├───────┼───────┼───────┤
* |   x   | x   x |   2   |
* |       |       |       |
* | x x   |       |   x x |
* └───────┴───────┴───────┘
* STEP2: exclusive every `num` at box/row/col
* ┌───────┬───────┬───────┐
* | x   y | x y x | y y x |
* | y y x | 2 x x | x y y |
* | y y x | y y y | 2 y y |
* ├───────┼───────┼───────┤
* | y y 2 | y x y | x y y |
* | y y y | x x x | y y   |
* | y y y | y     | y y   |
* ├───────┼───────┼───────┤
* | y x y | x y x | y 2 y |
* |     y | y     | y y y |
* | x x y | y     | y x x |
* └───────┴───────┴───────┘
* STEP3: check every box/row/col whether has the unique space to place `num`
* we found:
*   (1,2) at box1
*   (8,1) at col1
*   (5,9) at row5
*/

int Sudoku::stepNumber(int num) {
    int tips[81] = {0};
    int count = mCount;

    // STEP1: exclusive every item already has value
    for (int i = 0; i < 81; i++) {
        tips[i] = mData[i] != 0;
    }

    // STEP2: exclusive every `num` at box/row/col
    for (int i = 0; i < 81; i++) {
        if (mData[i] == num) {
            int indexs[9] = {0};
            Sudoku::getBoxIndex(i, indexs);
            signBoxWithIndexs(tips, indexs);
            Sudoku::getRowIndex(i, indexs);
            signBoxWithIndexs(tips, indexs);
            Sudoku::getColIndex(i, indexs);
            signBoxWithIndexs(tips, indexs);
        }
    }

    // STEP3: check every box/row/col whether has the unique space to place `num`
    for (int i = 0; i < 9; i++) {
        int indexs[9] = {0};
        int index = 0;

        // get box unique index
        Sudoku::getBoxIndex(boxIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != -1 && mData[index] == 0) {
            mData[index] = num;
            mCount++;
            outputDataStep(num, index, "exclusiveNumber by box", i);
        }

        // get row unique index
        Sudoku::getRowIndex(rowIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != -1 && mData[index] == 0) {
            mData[index] = num;
            mCount++;
            outputDataStep(num, index, "exclusiveNumber by row", i);
        }

        // get col unique index
        Sudoku::getColIndex(colIndexs[i], indexs);
        index = getBoxUniqueIndex(tips, indexs);
        if (index != -1 && mData[index] == 0) {
            mData[index] = num;
            mCount++;
            outputDataStep(num, index, "exclusiveNumber by col", i);
        }
    }

    return mCount-count;
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

void Sudoku::outputDataStep(int num, int index, const char * stepName, int i) {
// #define DEBUG
#ifdef DEBUG
    if (i != -1)
        printf("get number %d at %d:%d with %s %d\n",
                    num, index / 9 + 1, index % 9 + 1, stepName, i+1);
    else
        printf("get number %d at %d:%d with %s\n",
                    num, index / 9 + 1, index % 9 + 1, stepName);
    outputData();
    printf("data count:%d\n", count());
    printf("================================================================\n\n");
#endif
}

// =========================static functions===================================
void Sudoku::removeValuesWithDataIndexs(int * availables, int *data, int * indexs) {
    for (int i = 0; i < 9; i++) {
        int index = indexs[i];
        int value = data[index];
        if (value != 0) {
            availables[value-1] = 0;
        }
    }
}

void Sudoku::outputBox9(int box[], int index) {
    if (index != -1)
        printf("┌───┬─%d─┬───┐\n", index % 9 + 1);
    else
        printf("┌───┬───┬───┐\n");

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            if (index != -1 && i % 6 != 0)
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

/**
* check the box whether has unique item, if has return the index
* params: data: 9x9 data array with value 1 or 0
* params: indexs: 3x3 index array
* e.g.:  data array:
* ┌───────┬───────┬───────┐
* | 1   1 | 1 1 1 | 1 1 1 |
* | 1 1 1 | 1 1 1 | 1 1 1 |
* | 1 1 1 | 1 1 1 | 1 1 1 |
* ├───────┼───────┼───────┤
* | 1 1 1 | 1 1 1 | 1 1 1 |
* | 1 1 1 | 1 1 1 | 1 1   |
* | 1 1 1 | 1     | 1 1   |
* ├───────┼───────┼───────┤
* | 1 1 1 | 1 1 1 | 1 1 1 |
* |     1 | 1     | 1 1 1 |
* | 1 1 1 | 1     | 1 1 1 |
* └───────┴───────┴───────┘
* indexs: 0, 1, 2, 9, 10, 11, 18, 19, 20
* return:1
*/
int Sudoku::getBoxUniqueIndex(int * data, int * indexs) {
    int ret = -1;

    for (int i = 0; i < 9; i++) {
        int index = indexs[i];
        // get space, we sign it;
        if (data[index] == 0) {
            // if there's more space, just return -1
            if (ret != -1)
                return -1;

            ret = index;
        }
    }

    return ret;
}

void Sudoku::signBoxWithIndexs(int * box, int * indexs) {
    int index = 0;
    for (int i = 0; i < 9; i++) {
        index = indexs[i];
        box[index] = 1;
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

void Sudoku::getColIndex(int index, int * indexs) {
    int result[] = { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
    for (int i = 0; i < 9; i++) {
        indexs[i] = result[i] + index % 9;
    }
}

int Sudoku::checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type) {
    int flag[9] = {0};
    int box[9] = {0};
    int count = 0, index = -1;

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
            outputBox9(box);
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
