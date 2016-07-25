#include "mine.h"

int main(int argc, char** argv){
    unsigned int uiRow, uiCol;  /*A X B array.*/
    unsigned int mines; /*mines in a game*/
    char **game;
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
