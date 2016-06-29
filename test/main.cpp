
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "precanned.h"

using namespace std;

bool TestNoExistFile( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/NoExist.sudoku", data);
    return ret == expected;
}

bool TestEmptyFile( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/EmptyFile.sudoku", data);
    return ret == expected;
}

bool TestEmptyLine( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/EmptyLine.sudoku", data);
    return ret == expected;
}

bool TestColNumLessThan9( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/ColNumLessThan9.sudoku", data);
    return ret == expected;
}

bool TestColNumBiggerThan9( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/ColNumBiggerThan9.sudoku", data);
    return ret == expected;
}

bool TestValid( int expected ) {
    int data[81] = { 0 };
    int ret = Precanned::parseSudokuFile("res/Valid.sudoku", data);
    return ret == expected;
}

#define TEST_RUN(func, expected) \
    if ( !func(expected) ) {printf("%s test failed!\n", #func); return -1;} \
    else printf("%s test pass!\n", #func);

int main(int argc, char * argv[]) {
    TEST_RUN(TestNoExistFile, Precanned::ERR_FILE_NOTOPEN)
    TEST_RUN(TestEmptyFile, Precanned::ERR_FILE_EMPTY)
    TEST_RUN(TestEmptyLine, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestColNumLessThan9, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestColNumBiggerThan9, Precanned::ERR_BAD_LINE)
    TEST_RUN(TestValid, Precanned::ERR_NO_ERROR)
}
