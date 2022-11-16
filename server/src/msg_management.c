#include "../Include/proto.h"

/**
 * Check the validity of the request
 * @param SServerInfo pointer on the main class servSocketInfo
*/
int check_command(struct servSocketInfo *SServerInfo)
{
    switch (SServerInfo->game_board.case_modification(&SServerInfo->game_board, SServerInfo->buffer)) {
        case 0: // OK
            sendUpdateToEveryone(SServerInfo);
            break;
        case 1: // Case already taken
            send(SServerInfo->sd , CASEALREADYTAKEN , strlen(CASEALREADYTAKEN) , 0);
            break;
        default: // Error, display the normal command
            send(SServerInfo->sd , BADCOMMAND , strlen(BADCOMMAND) , 0);

    }

}

/**
 * Check if this is the good player who ask for play
 * @param SServerInfo pointer on the main class servSocketInfo
*/
int check_player(struct servSocketInfo *SServerInfo)
{
    if (SServerInfo->game_board.currentPlayer == 'x') {
        if (SServerInfo->sd == SServerInfo->x_player) {
            check_command(SServerInfo);
        } else {
            send(SServerInfo->sd , BADPLAYER , strlen(BADPLAYER) , 0 );
        }
    } else if (SServerInfo->game_board.currentPlayer == 'o') {
        if (SServerInfo->sd == SServerInfo->y_player) {
            check_command(SServerInfo);
        } else {
            send(SServerInfo->sd , BADPLAYER , strlen(BADPLAYER) , 0 );
        }
    }
}