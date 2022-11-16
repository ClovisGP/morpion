#include "../Include/proto.h"
#include "../Include/game_board.h"


/**
 * Initialize the game board
 * @param lenght the width and heigh of the board game
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

/**
 * Manage the change of a case
 * @param this_struct the struct which contain the gameboard
 * @param line the target line
 * @param col the target column
*/
int board_modification(struct gameBoard *this_struct, int line, int col)
{
    if (this_struct->board[line - 1][col - 1] == '-') {
        this_struct->board[line - 1][col - 1] = this_struct->currentPlayer;
        if (this_struct->currentPlayer == 'x') this_struct->currentPlayer = 'o';
        else this_struct->currentPlayer = 'x';
        return (0);
    }
    return (1);
}

/**
 * Pre-manage the change of a case
 * @param this_struct the struct which contain the gameboard
 * @param str_msg the request of the message
*/
int case_modification(struct gameBoard *this_struct, char *str_msg)
{
    char *delim = ":";
    char *str_tmp = strdup(str_msg);
    char *target_line = strtok(str_tmp, delim);
    char *target_col = strtok(NULL, delim);
    if (target_line && target_col) {
        int i_target_line = atoi(target_line);
        int i_target_col = atoi(target_col);
        if (i_target_line < 1 || i_target_line > this_struct->lenght) return (-1);
        if (i_target_col < 1 || i_target_col > this_struct->lenght) return (-1);
        free(str_tmp);
        return (board_modification(this_struct, i_target_line, i_target_col));
    } else {
        free(str_tmp);
        return (-1);
    }
}

/**
 * Create a new struct gameBoard and initialize it
 * @param board_size the width and height of the gameboard
*/
struct gameBoard gameBoardConstruct(int board_size) {
    struct gameBoard this_struct;
    this_struct.lenght = board_size;
    this_struct.currentPlayer = 'x';
    this_struct.board_generation = board_generation;
    this_struct.case_modification = case_modification;
    this_struct.board = this_struct.board_generation(this_struct.lenght);
    return (this_struct);
}

/**
 * Free all the object of the gameBoard struct
 * @param this_struct The target struct
*/
int gameBoardDestroy(struct gameBoard *this_struct)
{
    for (int indexArray = 0; this_struct->board[indexArray]; indexArray++) {
        free(this_struct->board[indexArray]);
    }
    free(this_struct->board);
    return (0);
}