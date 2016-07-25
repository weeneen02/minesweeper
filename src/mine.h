#ifndef __AA__
#define __AA__

/*
 * This is a mine.h file.
 * I don't know what I write here... 
 *
 * */
char** MakeGrid(unsigned int uiRow, unsigned int uiCol);
int SetMines(unsigned int n, char **grid, 
        const unsigned int cuiRow,
        const unsigned int cuiCol);

unsigned int SearchWindow(unsigned int uiRow, 
        unsigned int uiCol,
        char **gird);

int SetNumbers(char **grid,
        unsigned int uiRealRow,
        unsigned int uiRealCol);

void PrintGrid(char **grid);

#endif
