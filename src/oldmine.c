/*
File Name   : mine.c
exec Name   : mine
Author      : Lim Jae Hwan
Purpose     : Making a mine game. 
              User should give the size of arrays.
              You guys might know how to play this game.
              So I don't explain the rules.
Uses        : This is just used as an executable file.
Restricts   : We use a GNU Compiler in Linux, Ubuntu.
Error detec : 1. The arrays size.
              2. it should make sure how many mines in it.

Modify      : 07-15 start coding this C file.
                    Modify MakeGrid()
                    Editing SetMines()... 

              07-19 Editing MakeGrid() "We are gonna set number 9 all area first."
                    complete SetMines() function.

              07-20 complete. There were some errors.
                    One of them is mis allocating the rows
                    I was taught that we should include the null value in allocation.
                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    !!! I don't know why this program is so slow..? !!! 
                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Pseudo code
Before that. The array start number is 0. 
-------------------------Insert number------------------------------
1. Get the game size such as 3,3(3X3) 10,4(10X4)
2. Determine the number of mines. it should be less than 
   the multipled number you gave.
3. Get the number of mines from users.
-------------------------Making game.-------------------------------
4. If we get the X, Y numbers, Make two dimentions arrays [X+2][Y+2]
5. Input the mine randomly in the [X][Y] array.
6. Input the number the free parts in x,y array. We are gonna use
   the window [3X3] array. it's start from array[1][1] which is the
   center of array [3X3] array to array[X][Y].
--------------------------------------------------------------------
The fake array is [X+2][Y+2]. The real array is from [1][1] to [X][Y]
7. During window goes the array, it should count the mine around the 
   center cell. If nothing has a mine, the center cell is marked as
   '0'. If there are one or more than one, count them and mark the 
   number on the center cell.
8. The edge of the real array gets 0 or Null.
--------------------------------------------------------------------
9. We are gonna use System Function to give an effect of showing 
   the number or mine.
10.If user clicked the cell which has a mine. Game is over. and
   show the rest of mines. 
11.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char** argv){
    unsigned int uiRow, uiCol;  /*A X B array.*/
    unsigned int mines; /*mines in a game*/
    char **game = NULL;
    int i;

    printf("The size of game? (e.g if you want 3X3 size put 3,3)");
    scanf("%d,%d", &uiRow, &uiCol);
    
    game = MakeGrid(uiRow, uiCol);
    
    printf("How many mines?\n");
    scanf("%d", &mines);
    
    if ( SetMines(mines, game, uiRow, uiCol) == 1 ){
        printf("error over mine!\n");
        return 0;
    }
    
    if ( SetNumbers(game, uiRow, uiCol) == 0 ){
        printf("game is ready\n");
    }
    
    PrintGrid(game);

    /*free!!*/
    for ( i = 0; i < uiRow; i++ ){
        free(*(game + i));
    }
    free(game);
    
    return 0;
}
