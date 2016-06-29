
#ifndef _PRECANNED_H
#define _PRECANNED_H

class Precanned {

public:
    Precanned();
    ~Precanned();

static bool parseSudokuFile(const char * fileName, int * data);
static bool parseLine(char * line, int row, int * data);
};

#endif
