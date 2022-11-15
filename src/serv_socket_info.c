#include "../Include/serv_socket_info.h"

int sendUpdateToEveryone(struct servSocketInfo *thisStruct)
{
    for (int index = 0; index < thisStruct->max_clients; index++) {  
        // Ugly but I am short in time
        for (int indexLine = 0; thisStruct->game_board.board[indexLine]; indexLine++) {
            send(thisStruct->client_socket[index], thisStruct->game_board.board[indexLine], strlen(thisStruct->game_board.board[indexLine]), 0) != strlen(thisStruct->game_board.board[indexLine]);
        }
    }  
}

int sendFirstDisplay(struct servSocketInfo *thisStruct)
{
    // Ugly but I am short in time
    for (int indexLine = 0; thisStruct->game_board.board[indexLine]; indexLine++) {
        send(thisStruct->new_socket, thisStruct->game_board.board[indexLine], strlen(thisStruct->game_board.board[indexLine]), 0) != strlen(thisStruct->game_board.board[indexLine]);
    }  
}

/**
 * Create a new strcut servSocketInfo and initialize it
*/
struct servSocketInfo servSocketInfoConstruct(int port, int board_size)
{
    struct servSocketInfo thisStruct;
    thisStruct.port = port;
    thisStruct.is_server_running = true;
    thisStruct.opt = true;
    thisStruct.max_clients = 2;
    thisStruct.x_player = 0;
    thisStruct.y_player = 0;
    thisStruct.game_board = gameBoardConstruct(board_size);

    return (thisStruct);
}

/**
 * Free all the object of the servSocketInfo
*/
int servSocketInfoDestroy(struct servSocketInfo *thisStruct)
{
    return (0);
}
    