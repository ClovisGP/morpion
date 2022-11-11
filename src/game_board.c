#include "../Include/proto.h"
#include "../Include/game_board.h"


/**
 * Initialize the game board
*/
char **board_generation(int lenght)
{
    char **board = malloc(sizeof(char *) * (lenght + 2));

    if (!board) return (NULL);
    for (int indexArray = 0; indexArray < lenght; indexArray++) {
        board[indexArray] = malloc(sizeof(char) * (lenght + 2));
        if (!board[indexArray]) return (NULL);
        for (int indexcol = 0; indexcol < lenght; indexcol++) {
            board[indexArray][indexcol] = '-';
        }
        board[indexArray][lenght] = '\n';
        board[indexArray][lenght + 1] = '\0';
    }
    board[lenght] = NULL;
    return (board);
}

int board_modification(struct gameBoard *thisStruct, int line, int col)
{
    if (thisStruct->board[line - 1][col - 1] == '-') {
        thisStruct->board[line - 1][col - 1] = thisStruct->currentPlayer;
        if (thisStruct->currentPlayer == 'x') thisStruct->currentPlayer = 'o';
        else thisStruct->currentPlayer = 'x';
        return (0);
    }
    return (1);
}

int case_modification(struct gameBoard *thisStruct, char *str_msg) //function to has to be clean
{
    char *delim = ":";
    char *target_line = strtok_r(strdup(str_msg), delim, &str_msg);
    char *target_col = strtok_r(strdup(str_msg), delim, &str_msg);
    if (target_line && target_col) {
        int i_target_line = atoi(target_line);
        int i_target_col = atoi(target_col);
        if (i_target_line < 1 || i_target_line > thisStruct->lenght) return (-1);
        if (i_target_col < 1 || i_target_col > thisStruct->lenght) return (-1);
        return (board_modification(thisStruct, i_target_line, i_target_col));
    } else {
        return (-1);
    }
}

/**
 * Create a new strcut gameBoard and initialize it
*/
struct gameBoard gameBoardConstruct(void) {
    struct gameBoard thisStruct;
    thisStruct.lenght = 3;
    thisStruct.currentPlayer = 'x';
    thisStruct.board_generation = board_generation;
    thisStruct.case_modification = case_modification;
    thisStruct.board = thisStruct.board_generation(thisStruct.lenght);
    return (thisStruct);
}

/**
 * Free all the object of the gameBoard
*/
int gameBoardDestroy(struct gameBoard *thisStruct)
{
    for (int indexArray = 0; thisStruct->board[indexArray]; indexArray++) {
        free(thisStruct->board[indexArray]);
    }
    free(thisStruct->board);
    return (0);
}