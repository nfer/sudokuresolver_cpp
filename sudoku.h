
#ifndef _SUDOKU_H
#define _SUDOKU_H

class Sudoku {

public:
    Sudoku();
    Sudoku(int * data);
    ~Sudoku();

    void init(int * data);
    int  count() const;
    void outputData() const;
    void outputDataTips();

    void exclusiveRange();

private:
    Sudoku(const Sudoku& o);

    void outputBox(int index, int * box);

    void stepBox();
    void stepRow();
    void stepColumn();

    void updateDataTips(int i, int * indexs);
    void updateDataFromTips();

static int getIndex(int * tips);
static void getBoxIndex(int index, int * indexs);
static void getRowIndex(int index, int * indexs);
static void getColumnIndex(int index, int * indexs);

private:
    int * data;
    int * dataExcl;
    int ** dataTips;
};

#endif
