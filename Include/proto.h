
#ifndef PROTO_H_
#define PROTO_H_

// #include <unistd.h>
// #include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_board.h"
#include <errno.h> 
#include <unistd.h>   //close 
#include "serv_socket_info.h"
#include <sys/time.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include "com_data.h"

// #define ERROR_CODE -1
// #define SUCCESS_CODE 0
// #define MAX_BUFF_SIZE 4096
// #define SOCKST struct sockaddr_in


void new_connection(struct servSocketInfo *SServerInfo);
int player_assign(struct servSocketInfo *SServerInfo);
int check_player(struct servSocketInfo *SServerInfo);

#endif /* !PROTO_H_ */