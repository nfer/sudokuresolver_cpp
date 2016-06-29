
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "precanned.h"

using namespace std;

bool TestPrecannedNoExistFile( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/NoExist.sudoku", data);
    return ret == expected;
}

bool TestPrecannedEmptyFile( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/EmptyFile.sudoku", data);
    return ret == expected;
}

bool TestPrecannedEmptyLine( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/EmptyLine.sudoku", data);
    return ret == expected;
}

bool TestPrecannedColNumLessThan9( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/ColNumLessThan9.sudoku", data);
    return ret == expected;
}

bool TestPrecannedColNumBiggerThan9( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/ColNumBiggerThan9.sudoku", data);
    return ret == expected;
}

bool TestPrecannedValid( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/Valid.sudoku", data);
    return ret == expected;
}

bool TestSudokuColDuplicate( int expected ) {
    int data[] = {  0, 0, 0, 0, 2, 3, 0, 1, 0,
                    0, 3, 0, 0, 7, 0, 0, 0, 6,
                    0, 7, 0, 9, 0, 0, 0, 0, 2,
                    0, 1, 6, 0, 0, 0, 0, 3, 0,
                    0, 0, 0, 4, 0, 9, 0, 0, 0,
                    0, 2, 0, 0, 0, 0, 8, 5, 0,
                    1, 0, 0, 0, 2, 8, 0, 7, 0,
                    7, 0, 0, 0, 4, 0, 0, 8, 0,
                    0, 4, 0, 2, 5, 0, 0, 0, 0};
    Sudoku * sudoku = new Sudoku(data);
    int ret = sudoku->valid();
    return ret == expected;
}

bool TestSudokuRowDuplicate( int expected ) {
    int data[] = {  0, 0, 0, 0, 2, 3, 0, 1, 0,
                    0, 3, 0, 0, 7, 0, 0, 0, 6,
                    0, 7, 0, 9, 0, 0, 0, 0, 2,
                    0, 1, 6, 0, 0, 0, 0, 3, 0,
                    0, 0, 0, 4, 0, 9, 0, 0, 0,
                    0, 2, 0, 0, 0, 0, 8, 5, 0,
                    1, 0, 0, 0, 0, 8, 0, 7, 0,
                    7, 0, 0, 0, 4, 0, 0, 8, 0,
                    0, 4, 0, 2, 5, 0, 0, 0, 5};
    Sudoku * sudoku = new Sudoku(data);
    int ret = sudoku->valid();
    return ret == expected;
}

bool TestSudokuBoxDuplicate( int expected ) {
    int data[] = {  0, 0, 0, 0, 2, 3, 0, 1, 0,
                    0, 3, 0, 0, 7, 0, 0, 0, 6,
                    0, 7, 0, 9, 0, 0, 0, 0, 2,
                    0, 1, 6, 0, 0, 0, 0, 3, 0,
                    0, 0, 0, 4, 0, 9, 0, 0, 0,
                    0, 2, 0, 0, 0, 0, 8, 5, 0,
                    1, 0, 0, 0, 0, 8, 0, 7, 0,
                    7, 0, 0, 0, 4, 0, 0, 8, 0,
                    0, 4, 0, 2, 5, 0, 0, 0, 8};
    Sudoku * sudoku = new Sudoku(data);
    int ret = sudoku->valid();
    return ret == expected;
}

bool TestSudokuValid( int expected ) {
    int data[] = {  0, 0, 0, 0, 2, 3, 0, 1, 0,
                    0, 3, 0, 0, 7, 0, 0, 0, 6,
                    0, 7, 0, 9, 0, 0, 0, 0, 2,
                    0, 1, 6, 0, 0, 0, 0, 3, 0,
                    0, 0, 0, 4, 0, 9, 0, 0, 0,
                    0, 2, 0, 0, 0, 0, 8, 5, 0,
                    1, 0, 0, 0, 0, 8, 0, 7, 0,
                    7, 0, 0, 0, 4, 0, 0, 8, 0,
                    0, 4, 0, 2, 5, 0, 0, 0, 0};
    Sudoku * sudoku = new Sudoku(data);
    int ret = sudoku->valid();
    return ret == expected;
}

#define TEST_RUN(func, expected) \
    if ( !func(expected) ) {printf("%s test failed!\n", #func); return -1;} \
    else printf("%s test pass!\n", #func);

int main(int argc, char * argv[]) {
    TEST_RUN(TestPrecannedNoExistFile, Precanned::ERR_FILE_NOTOPEN)
    TEST_RUN(TestPrecannedEmptyFile, Precanned::ERR_FILE_EMPTY)
    TEST_RUN(TestPrecannedEmptyLine, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestPrecannedColNumLessThan9, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestPrecannedColNumBiggerThan9, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestPrecannedValid, Precanned::ERR_NO_ERROR)

    TEST_RUN(TestSudokuColDuplicate, Sudoku::ERR_COL_DUPLICATE)
    TEST_RUN(TestSudokuRowDuplicate, Sudoku::ERR_ROW_DUPLICATE)
    TEST_RUN(TestSudokuBoxDuplicate, Sudoku::ERR_BOX_DUPLICATE)
    TEST_RUN(TestSudokuValid, Sudoku::ERR_NO_ERROR)
}
