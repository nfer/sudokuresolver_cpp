
#ifndef _PRECANNED_H
#define _PRECANNED_H

class Precanned {

public:
	enum {
		ERR_NO_ERROR = 0,
		ERR_FILE_NOTOPEN = -1,
		ERR_FILE_EMPTY = -2,
		ERR_BAD_LINE = -3, // col number isn't 9
		ERR_BAD_ROW = -4 // row number isn't 9
	} Precanned_Error;
    Precanned();
    ~Precanned();

static int parseSudokuFile(const char * fileName, int * data);
static bool parseLine(char * line, int row, int * data);
};

#endif
