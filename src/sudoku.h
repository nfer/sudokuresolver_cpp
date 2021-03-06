
#ifndef _SUDOKU_H
#define _SUDOKU_H

#ifndef SUDOKU_DEBUG
#define SUDOKU_DEBUG 0
#endif

class Sudoku {

public:
    enum CHECK_VALID_TYPE {
        NODUP,
        UNIQUE,
        FULL
    };
    enum {
        ERR_NO_ERROR = 0,
        ERR_COL_DUPLICATE = -1,
        ERR_ROW_DUPLICATE = -2,
        ERR_BOX_DUPLICATE = -3,
    } Sudoku_Error;

    Sudoku();
    Sudoku(int * data);
    ~Sudoku();

    void init(int * data);
    void initTips();
    int  valid();
    int  count() const {return mCount;};
    void outputData();
    void outputDataTips();
    void outputDataTips81();

    bool exclusiveRange();
    bool exclusiveNumber();

private:
    Sudoku(const Sudoku& o);

    int  stepIndex(int index);
    int  stepNumber(int num);

    void updateDataTips(int value, int index);
    void updateDataFromTips();

    void outputDataStep(int num, int index, const char * stepName, int i = -1);

/**
* out a 9 size array like below format:
* if index != -1:
* ┌───┬─7─┬───┐
* │ 1 │ 2 │ 3 │
* ├───┼───┼───┤
* 8 4 │ 5 │ 6 │
* ├───┼───┼───┤
* │ 7 │ 8 │ 9 │
* └───┴───┴───┘
* else:
* ┌───┬───┬───┐
* │ 1 │ 2 │ 3 │
* ├───┼───┼───┤
* │ 4 │ 5 │ 6 │
* ├───┼───┼───┤
* │ 7 │ 8 │ 9 │
* └───┴───┴───┘
*/
static void outputBox9(int * box, int index = -1);

/**
* out a 81 size array like below format:
*    1 2 3   4 5 6   7 8 9  
*  ┌───────┬───────┬───────┐
* 1|       | 6 2 3 | 7 1 8 |
* 2| 2 3 1 | 8 7 4 | 5 9 6 |
* 3| 6 7 8 | 9 1 5 | 3 4 2 |
*  ├───────┼───────┼───────┤
* 4|   1 6 | 5 8 2 |   3 7 |
* 5| 5 8 7 | 4 3 9 | 6 2 1 |
* 6| 3 2   | 7 6 1 | 8 5   |
*  ├───────┼───────┼───────┤
* 7| 1 6   | 3 9 8 |   7   |
* 8| 7     | 1 4 6 |   8   |
* 9| 8 4   | 2 5 7 | 1 6   |
*  └───────┴───────┴───────┘
*    1 2 3   4 5 6   7 8 9 
* NOTE: space means it's value is zore or undefined
*/
static void outputBox81(int * box);


static void outputBox729(int mTips[81][9]);

/**
* return the box indexs array of given index.
* e.g.: for any index  in 0,1,2 or 9, 10, 11 or 18, 19, 20
* always return: { 0, 1, 2, 9, 10, 11, 18, 19, 20 }
*/
static void getBoxIndex(int index, int * indexs);

/**
* return the row indexs array of given index.
* e.g.: for any index  in 0, 1, 2, 3, 4, 5, 6, 7, 8
* always return: { 0, 1, 2, 3, 4, 5, 6, 7, 8 }
*/
static void getRowIndex(int index, int * indexs);

/**
* return the col indexs array of given index.
* e.g.: for any index  in 0, 9, 18, 27, 36, 45, 54, 63, 72
* always return: { 0, 9, 18, 27, 36, 45, 54, 63, 72 }
*/
static void getColIndex(int index, int * indexs);

/**
* sign all items in given box/row/col with value 1
* params: box: 9x9 data array with value 1 or 0
* params: indexs: 9 size indexs array(from getBoxIndex/getRowIndex/getColIndex)
*/
static void signBoxWithIndexs(int * box, int * indexs);

/**
* remove values in available values set
* params: availables: 9 data array with value [0-9]
* params: box: 9x9 data array with value [0-9]
* params: indexs: 9 size indexs array(from getBoxIndex/getRowIndex/getColIndex)
*/
static void removeValuesWithDataIndexs(int * availables, int *data, int * indexs);


static void removeTipsWithDataIndexs(int tips[81][9], int indexs[9], int value);

static int  getIndex(int * tips);
static int  getBoxUniqueIndex(int * box, int * indexs);
static int  checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type);

private:
    int mData[81];
    int mTips[81][9];
    int mCount;
};

#endif
