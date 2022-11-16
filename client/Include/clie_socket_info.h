#ifndef SERV_SOCKET_INFO_H_
#define SERV_SOCKET_INFO_H_

#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


struct clie_socket_info {
    bool is_cli_running;
    int port;
    int sockfd;
    int connfd;
    int fd_list[2];
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;
    fd_set rfds;
    int sd;
    char buff[1024];
};

struct clie_socket_info clie_socket_info_construct(int port);
int clie_socket_info_destroy(struct clie_socket_info *thisStruct);

#endif /* !SERV_SOCKET_INFO_H_ */