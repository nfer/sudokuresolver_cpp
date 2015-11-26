
#ifndef _SUDOKU_H
#define _SUDOKU_H

class Sudoku {

public:
    enum CHECK_VALID_TYPE {
        NODUP,
        UNIQUE,
        FULL
    };

    Sudoku();
    Sudoku(int * data);
    ~Sudoku();

    void init(int * data);
    bool valid();
    int  count() const {return mCount;};
    void outputData();
    void outputDataTips();

    bool exclusiveRange();
    bool exclusiveNumber();

private:
    Sudoku(const Sudoku& o);

    void stepBox();
    void stepRow();
    void stepColumn();

    int  stepIndex(int index);
    int  stepNumber(int num);

    void updateDataTips(int i, int * indexs);
    void updateDataFromTips();

    void outputDataStep(int num, int index, const char * stepName);

static void removeTipsWithDataIndexs(int * tips, int *data, int * indexs, int len);
static void outputBox9(int index, int * box);
static void outputBox81(int * box);
static int  getIndex(int * tips);
static int  getBoxUniqueIndex(int * box, int * indexs);
static void setBox(int * box, int * indexs, int len, int value);
static void getBoxIndex(int index, int * indexs);
static void getRowIndex(int index, int * indexs);
static void getColumnIndex(int index, int * indexs);
static int  checkDataWithIndexs(int * data, int * indexs, CHECK_VALID_TYPE type);

private:
    int * mData;
    int ** mTips;
    int mCount;
};

#endif
