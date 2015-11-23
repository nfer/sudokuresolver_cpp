
#ifndef _SUDOKU_H
#define _SUDOKU_H

class Sudoku {

public:
    Sudoku();
    Sudoku(int * data);
    ~Sudoku();

    void init(int * data);
    int  count() const;
    void outputData();
    void outputDataTips();

    void exclusiveRange();
    void exclusiveNumber();

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

private:
    int * data;
    int * dataExcl;
    int ** dataTips;
};

#endif
