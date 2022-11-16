#include "../Include/serv_socket_info.h"

/**
 * Send the gameboard updated to every client
 * @param this_struct pointer on the main class servSocketInfo
*/
int sendUpdateToEveryone(struct servSocketInfo *this_struct)
{
    for (int index = 0; index < this_struct->max_clients; index++) {  
        // Ugly but I am short in time
        for (int indexLine = 0; this_struct->game_board.board[indexLine]; indexLine++) {
            send(this_struct->client_socket[index], this_struct->game_board.board[indexLine], strlen(this_struct->game_board.board[indexLine]), 0) != strlen(this_struct->game_board.board[indexLine]);
        }
        send(this_struct->client_socket[index], "**********\n", strlen("**********\n"), 0) != strlen("**********\n");
    }
    return (0);
}

/**
 * Send the QUIT to every client 
 * @param this_struct pointer on the main class servSocketInfo
*/
int sendQUITToEveryone(struct servSocketInfo *this_struct)
{
    for (int index = 0; index < this_struct->max_clients; index++) {
        // Because i is the socket which is already closed
        if (index != this_struct->i)
            send(this_struct->client_socket[index], QUIT, strlen(QUIT), 0) != strlen(QUIT);
    }
    return (0);
}

/**
 * Send the gameboard to the new client
 * @param this_struct pointer on the main class servSocketInfo
*/
int sendFirstDisplay(struct servSocketInfo *this_struct)
{
    // Ugly but I am short in time
    for (int indexLine = 0; this_struct->game_board.board[indexLine]; indexLine++) {
        send(this_struct->new_socket, this_struct->game_board.board[indexLine], strlen(this_struct->game_board.board[indexLine]), 0) != strlen(this_struct->game_board.board[indexLine]);
    }  
    send(this_struct->new_socket, "**********\n", strlen("**********\n"), 0) != strlen("**********\n");
    return (0);
}

/**
 * Create a new struct servSocketInfo and initialize it
 * @param port it is the server port
 * @param board_size it is the server port
*/
struct servSocketInfo servSocketInfoConstruct(int port, int board_size)
{
    struct servSocketInfo this_struct;
    this_struct.port = port;
    this_struct.is_server_running = true;
    this_struct.opt = true;
    this_struct.max_clients = 2;
    this_struct.x_player = 0;
    this_struct.y_player = 0;
    this_struct.game_board = gameBoardConstruct(board_size);

    return (this_struct);
}

/**
 * Free all the object of the servSocketInfo
 * @param this_struct pointer on the main class servSocketInfo
*/
int servSocketInfoDestroy(struct servSocketInfo *this_struct)
{
    gameBoardDestroy(&this_struct->game_board);
    return (0);
}
    