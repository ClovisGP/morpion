
#ifndef PROTO_H_
#define PROTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_board.h"
#include <errno.h> 
#include <unistd.h>
#include "serv_socket_info.h"
#include <sys/time.h>

// #define ERROR_CODE -1
// #define SUCCESS_CODE 0
// #define MAX_BUFF_SIZE 4096
// #define SOCKST struct sockaddr_in


void new_connection(struct servSocketInfo *SServerInfo);
int player_assign(struct servSocketInfo *SServerInfo);
int check_player(struct servSocketInfo *SServerInfo);
int find_port(int ac , char *av[]);
int find_board_size(int ac , char *av[]);

#endif /* !PROTO_H_ */