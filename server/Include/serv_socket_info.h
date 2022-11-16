#ifndef SERV_SOCKET_INFO_H_
#define SERV_SOCKET_INFO_H_

#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include "game_board.h"
#include <string.h>

#define WELCOMEMESSAGEX "Welcome, you are the x player.\n\0"
#define WELCOMEMESSAGEO "Welcome, you are the o player.\n\0"
#define WELCOMEMESSAGENO "Welcome, sorry but two players are already connected but you can watch the game.\n\0"
#define BADPLAYER "Sorry but it is not your turn.\n\0"
#define BADCOMMAND "The comand must be LINE:COLUMN and must be a coordinate of the game board like example 1:2\n\0"
#define CASEALREADYTAKEN "This case is already taken, please enter a valide position\n\0"
#define YOURTURN "your turn to play\n\0"
#define QUIT "QUIT : A player was deconnected\n\0"

struct servSocketInfo {
    bool is_server_running;
    int opt;  
    int master_socket;
    int addrlen;
    int new_socket;
    int client_socket[30];
    int max_clients;
    int activity;
    int i;
    int valread;
    int sd;  
    int max_sd;
    int port;
    struct sockaddr_in address;
    char buffer[1025]; 
    fd_set readfds;
    int x_player;
    int y_player;
    struct gameBoard game_board;

};

int sendUpdateToEveryone(struct servSocketInfo *thisStruct);
int sendQUITToEveryone(struct servSocketInfo *thisStruct);
struct servSocketInfo servSocketInfoConstruct(int port, int board_size);
int servSocketInfoDestroy(struct servSocketInfo *thisStruct);
int sendFirstDisplay(struct servSocketInfo *thisStruct);

#endif /* !SERV_SOCKET_INFO_H_ */