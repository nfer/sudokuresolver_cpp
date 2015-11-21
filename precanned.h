
#ifndef _PRECANNED_H
#define _PRECANNED_H

class Precanned {

public:
    Precanned();
    ~Precanned();

static bool parse(int argc, char * argv[], int * data);
static bool parseLine(char * line, int row, int * data);
};

#endif
