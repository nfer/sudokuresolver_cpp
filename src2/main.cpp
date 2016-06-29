
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "precanned.h"

using namespace std;

int main(int argc, char * argv[])
{
    int count = 0;
    int data[81] = {0};

    if ( argc < 2 ) {
        return -1;
    }

    if ( Precanned::parseSudokuFile(argv[argc-1], data) != Precanned::ERR_NO_ERROR ) {
        printf("Parse Sudoku File failed\n");
        return 0;
    }

    Sudoku * sudoku = new Sudoku(data);
    if ( sudoku->valid() != Sudoku::ERR_NO_ERROR ) {
        printf("Precanned data is not valid.\n");
        goto end;
    }

    sudoku->outputData();
    count = sudoku->count();
    printf("init data count %d\n", count);
    printf("\n\n\n");
    sudoku->outputDataTips();

end:
    delete sudoku;
    return (count != 81);
}
