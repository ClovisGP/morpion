
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

#define ERROR_CODE -1
#define SUCCESS_CODE 0
#define MAX_BUFF_SIZE 4096
#define SOCKST struct sockaddr_in


int find_board_size(int ac , char *av[]);
void new_connection(struct servSocketInfo *SServerInfo);
int player_assign(struct servSocketInfo *SServerInfo);
int check_player(struct servSocketInfo *SServerInfo);
int find_port(int ac , char *av[]);

/*
Did you know the story of an optimistic guy?
As he fell from an immense height,
on each floor he said "Jusqu'ici, tout va bien" (translation: "so far all is well") while laughing.
And no, there is no end to this story, just a fall (French pun).*/

#endif /* !PROTO_H_ */