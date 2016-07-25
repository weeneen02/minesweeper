/*
 * This program is mines_functions.c 
 * It has essencial funcions to run minesweeper game.
 * Each function has the explanation. 
 * Author   :   JaeHwan Lim.
 * Email    :   weeneen02@gmail.com
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mine.h"

/* 
   This function is making the whole arrays by using parameters.
   The return value is a double pointer.
   We use the malloc function to make arrays. 
*/
char** MakeGrid(unsigned int uiRow, unsigned int uiCol){
    char** grid = NULL;
    int i, j;
    
    grid = (char**)malloc(sizeof(char*) * (uiRow + 3));
    memset(grid, 0, sizeof(char*) * (uiRow + 3));
    for ( i = 0; i < uiRow + 2; i++ ){
        *(grid + i) = (char*)malloc(sizeof(char) * (uiCol +1));
        
        for ( j = 0; j < uiCol + 1; j++ ){
            *(*(grid + i) + j) = '9';
        }
        *(*(grid + i) + j) = '\0';
    }
    printf("Init grid complete!\n");
    wait(1);
    return grid;
}


/*
   This function makes the number of mines in the arrays randomly.
   and the seed of rand() is time. We get the unique numbers
   according to the number 'n' from 1 to X*Y.
 */
int SetMines(unsigned int n, char **grid, const unsigned int cuiRow, const unsigned int cuiCol){
    int i;  /*for loop.*/
    time_t t;   /* the time seed of srand() */
    char *pCount = NULL;
    unsigned int uiInRow, uiInCol;
    unsigned int uiRandVal; /*random values*/ 
    unsigned int uiTot; /*uiRow X uiCol*/
    unsigned int uiVal;   /*0 ~ uiTot*/
       
    /*get the number of cubes (size) XxY*/
    uiTot = cuiRow * cuiCol;

    /*Error*/
    if ( uiTot <= n ) {
        fflush(stdin);
        printf("Error : mine overflow\n");
        return 1;
    }

    /* set mines */
    for ( i = 0; i < n; i++ ){
        srand((unsigned) time(&t));
        uiRandVal = rand();
        uiVal = (uiRandVal % uiTot);    /*0 ~ uiTot*/
        uiInRow = ( uiVal / cuiCol ) + 1;
        uiInCol = ( uiVal % cuiCol ) + 1;

        if ( *(*(grid + uiInRow) + uiInCol) == '*' ){
            i--;
            continue;
        }

        else {
            *(*(grid + uiInRow) + uiInCol) = '*';
        }
    }
    fflush(stdout);
    printf("Set mines complete!\n");
    return 0;
}


/*
 * This function is counting the mines in the around the center (row, col).
 * */
unsigned int SearchWindow(unsigned int uiRow, unsigned int uiCol, char** grid){
    unsigned int count = 0; /*mine number*/
    unsigned int uiCentRow;   /*the center row value*/
    unsigned int uiCentCol;   /*the center column value*/
    int i; 
    
    for ( uiCentRow = ( uiRow - 1); uiCentRow <= (uiRow + 1); uiCentRow++ ){
        for ( uiCentCol = ( uiCol - 1); uiCentCol <= (uiCol + 1); uiCentCol++){
            if ( *(grid + uiCentRow) + uiCentCol == '\0' ){
                break;
            }

            else if( *(*(grid + uiCentRow) + uiCentCol) == '*' ){
                count++;
            }
        }
    }
    return count;
}

/*
   This function sets numbers the rest of the grid.
   The number depends on the sum of mines in 3X3 area. 
 */
int SetNumbers(char **grid, unsigned int uiRealRow, unsigned int uiRealCol){
    int i, j; 
    unsigned int num;  /*mine number around the center.*/
    
    for ( i = 1; i <= uiRealRow; i++ ){
        for ( j = 1; j <= uiRealCol; j++ ){
            if ( *(*(grid + i) + j) == '*' ){
                continue;
            }

            else {
                num = SearchWindow((unsigned int)i,(unsigned int)j, grid);
                *(*(grid + i) + j) = num + 48;
            }
        }
    }
    return 0;
}



/*
   This function prints the whole arrays in the grid. This function
   will be used when needs to show it after one cell is clicked.
 */
void PrintGrid(char **grid){
    int i,j;

    //fflush(stdout);
    system("clear");

    for ( i = 1; *(grid + (i+1)) != NULL; i++ ){
        for ( j = 1; *(*(grid + i) + j) != '\0'; j++ ){
            printf("%c", *(*(grid + i) + j));
        }
        //fflush(stdout);
        printf("\n");
    }
    //fflush(stdout);
    printf("\n");

    printf("print complete\n");
}


