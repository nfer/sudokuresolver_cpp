
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "precanned.h"

using namespace std;

bool TestEmptyFile( bool expected ) {
    int data[81] = { 0 };
    bool ret = Precanned::parseSudokuFile("res/EmptyFile.sudoku", data);
    return ret == expected;
}

bool TestEmptyLine( bool expected ) {
    int data[81] = { 0 };
    bool ret = Precanned::parseSudokuFile("res/EmptyLine.sudoku", data);
    return ret == expected;
}

bool TestColNumLessThan9( bool expected ) {
    int data[81] = { 0 };
    bool ret = Precanned::parseSudokuFile("res/ColNumLessThan9.sudoku", data);
    return ret == expected;
}

bool TestColNumBiggerThan9( bool expected ) {
    int data[81] = { 0 };
    bool ret = Precanned::parseSudokuFile("res/ColNumBiggerThan9.sudoku", data);
    return ret == expected;
}

bool TestValid( bool expected ) {
    int data[81] = { 0 };
    bool ret = Precanned::parseSudokuFile("res/Valid.sudoku", data);
    return ret == expected;
}

#define TEST_RUN(func, expected) \
    if ( !func(expected) ) {printf("%s test failed!\n", #func); return -1;} \
    else printf("%s test pass!\n", #func);

int main(int argc, char * argv[]) {
    TEST_RUN(TestEmptyFile, false)
    TEST_RUN(TestEmptyLine, false)
    TEST_RUN(TestColNumLessThan9, false)
    TEST_RUN(TestColNumBiggerThan9, false)
    TEST_RUN(TestValid, true)
}
