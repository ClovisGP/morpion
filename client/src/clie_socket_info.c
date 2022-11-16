#include "../Include/clie_socket_info.h"

struct clie_socket_info clie_socket_info_construct(int port)
{
    struct clie_socket_info this_struct;
    this_struct.port = port;
    this_struct.is_cli_running = true;

    this_struct.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this_struct.sockfd == -1) {
        printf("socket creation failed...\n");
        exit(-1);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&this_struct.servaddr, sizeof(this_struct.servaddr));
    this_struct.servaddr.sin_family = AF_INET;
    this_struct.servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    this_struct.servaddr.sin_port = htons(this_struct.port);
    if (connect(this_struct.sockfd, (SA*)&this_struct.servaddr, sizeof(this_struct.servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(-1);
    } else {
        printf("connected to the server..\n");
    }
    this_struct.fd_list[0] = 0;
    this_struct.fd_list[1] = this_struct.sockfd;
    return (this_struct);
}

int clie_socket_info_destroy(struct clie_socket_info *thisStruct)
{

}