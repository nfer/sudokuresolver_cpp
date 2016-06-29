
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
    int  valid();
    int  count() const {return mCount;};
    void outputData();

    bool exclusiveRange();
    bool exclusiveNumber();

private:
    Sudoku(const Sudoku& o);

    void outputDataStep(int num, int index, const char * stepName, int i = -1);

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

static int  checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type);

private:
    int mData[81];
    int mTips[729];
    int mCount;
};

#endif
