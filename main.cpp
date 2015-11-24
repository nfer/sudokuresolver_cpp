
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "precanned.h"

using namespace std;

int main(int argc, char * argv[])
{
    // easy mode
    // int data[] = {  0, 1, 0, 8, 0, 5, 0, 3, 0,
    //                 0, 7, 0, 9, 0, 2, 0, 1, 0,
    //                 0, 0, 8, 1, 0, 6, 7, 0, 0,
    //                 4, 0, 0, 0, 0, 0, 0, 0, 1,
    //                 3, 5, 0, 0, 0, 0, 0, 8, 2,
    //                 7, 0, 0, 0, 0, 0, 0, 0, 3,
    //                 0, 0, 4, 6, 0, 1, 2, 0, 0,
    //                 0, 6, 0, 3, 0, 4, 0, 5, 0,
    //                 0, 9, 0, 7, 0, 8, 0, 4, 0};
    // medium mode
    int data[] = {  6, 0, 0, 4, 0, 8, 0, 0, 9,
                    0, 0, 9, 2, 5, 6, 3, 0, 0,
                    0, 0, 3, 0, 0, 0, 2, 0, 0,
                    0, 0, 2, 0, 8, 0, 4, 0, 0,
                    0, 0, 0, 9, 7, 5, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 8, 0, 1, 0, 7, 0, 2, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0,
                    7, 4, 0, 0, 0, 0, 0, 8, 6};
    int countBefore, countAfter = 0, loop = 0;

    if (!Precanned::parse(argc, argv, data)) {
        cout << "Precanned parse failed" << endl;
        return 0;
    }

    Sudoku * sudoku = new Sudoku(data);
    if (!sudoku->valid()) {
        cout << "the precanned data is not valid." << endl;
        delete sudoku;
        return 0;
    }

    sudoku->outputData();
    countBefore = sudoku->count();
    cout << "data count:" << countBefore << endl;

    while (countBefore != countAfter && countAfter != 81) {
        countBefore = countAfter;
        sudoku->exclusiveRange();
        countAfter = sudoku->count();
        loop++;
    }
    sudoku->outputData();
    cout << "after exclusiveRange data count:" << countAfter << endl;
    cout << "exclusiveRange loop count:" << loop << endl;

    countAfter = -1;
    while (countBefore != countAfter && countAfter != 81) {
        countBefore = countAfter;
        sudoku->exclusiveNumber();
        sudoku->exclusiveRange();
        countAfter = sudoku->count();
        loop++;
    }
    sudoku->outputData();
    cout << "after exclusiveNumber data count:" << countAfter << endl;
    cout << "exclusiveNumber loop count:" << loop << endl;

    delete sudoku;
    return 0;
}
