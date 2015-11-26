
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
    int count, lastCount = -1, loop;
    bool found;

    if (!Precanned::parse(argc, argv, data)) {
        printf("Precanned parse failed\n");
        return 0;
    }

    Sudoku * sudoku = new Sudoku(data);
    if (!sudoku->valid()) {
        printf("Precanned data is not valid.\n");
        goto end;
    }

    sudoku->outputData();
    count = sudoku->count();
    printf("init data count %d\n", count);

start:
    // check endless loop
    if (count == lastCount)
        goto end;
    lastCount = count;

    // exclusiveRange check loop
    found = false;
    loop = 0;
    do {
        found = sudoku->exclusiveRange();
        loop++;
    } while (found);
    sudoku->outputData();
    count = sudoku->count();
    printf("exclusiveRange loop %d, %d data now\n", loop, count);
    if (count == 81)
        goto end;

    // exclusiveNumber check loop
    found = false;
    loop = 0;
    do {
        found = sudoku->exclusiveNumber();
        loop++;
    } while (found);
    sudoku->outputData();
    count = sudoku->count();
    printf("exclusiveNumber loop %d, %d data now\n", loop, count);
    if (count == 81)
        goto end;
    else
        goto start;

end:
    delete sudoku;
    return (count != 81);
}
