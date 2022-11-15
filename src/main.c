/*
Le client
Voir un systeme qui detecte si tu gagne
opti certain offichage
*/

#include "../Include/proto.h"

int close_socket(struct servSocketInfo *SServerInfo)
{
    int tmp_sd = SServerInfo->sd;
    getpeername(SServerInfo->sd , (struct sockaddr*)&(SServerInfo->address) , \
        (socklen_t*)&(SServerInfo->addrlen));  
    printf("Host disconnected , ip %s , port %d \n" , \
            inet_ntoa(SServerInfo->address.sin_addr) , ntohs(SServerInfo->address.sin_port));
    close(SServerInfo->sd);  
    SServerInfo->client_socket[SServerInfo->i] = 0;
    if (tmp_sd == SServerInfo->x_player) {
        SServerInfo->x_player = 0;
        SServerInfo->is_server_running = false;
    } else if (tmp_sd == SServerInfo->y_player) {
        SServerInfo->y_player = 0;
        SServerInfo->is_server_running = false;
    }
    return (0);
}

int serverInitialization(struct servSocketInfo *SServerInfo)
{
    for (SServerInfo->i = 0; SServerInfo->i < SServerInfo->max_clients; SServerInfo->i++) {  
        SServerInfo->client_socket[SServerInfo->i] = 0;  
    }
    if((SServerInfo->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }
    if(setsockopt(SServerInfo->master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&(SServerInfo->opt), sizeof(SServerInfo->opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    SServerInfo->address.sin_family = AF_INET;  
    SServerInfo->address.sin_addr.s_addr = INADDR_ANY;  
    SServerInfo->address.sin_port = htons(SServerInfo->port);
    if (bind(SServerInfo->master_socket, (struct sockaddr *)&SServerInfo->address, sizeof(SServerInfo->address)) < 0) {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", SServerInfo->port);  
    if (listen(SServerInfo->master_socket, 2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);  
    }
    SServerInfo->addrlen = sizeof(SServerInfo->address);  
    puts("Waiting for connections ...");
    return (0);
}
    
int main(int ac, char *av[])  
{
    int tmp_port = find_port(ac, av);
    if (tmp_port == -1) return (-1);
    struct servSocketInfo SServerInfo = servSocketInfoConstruct(tmp_port, find_board_size(ac, av));
    serverInitialization(&SServerInfo);

    while(SServerInfo.is_server_running) { 
        FD_ZERO(&(SServerInfo.readfds));  
        FD_SET(SServerInfo.master_socket, &(SServerInfo.readfds));  
        SServerInfo.max_sd = SServerInfo.master_socket;  
        for (SServerInfo.i = 0; SServerInfo.i < SServerInfo.max_clients; SServerInfo.i++) {  
            SServerInfo.sd = SServerInfo.client_socket[SServerInfo.i];  
            if(SServerInfo.sd > 0) FD_SET( SServerInfo.sd , &(SServerInfo.readfds));  
            if(SServerInfo.sd > SServerInfo.max_sd) SServerInfo.max_sd = SServerInfo.sd;  
        }
        SServerInfo.activity = select( SServerInfo.max_sd + 1 , &(SServerInfo.readfds) , NULL , NULL , NULL);  
        if ((SServerInfo.activity < 0) && (errno != EINTR)) printf("select error");
        new_connection(&SServerInfo);
        for (SServerInfo.i = 0; SServerInfo.i < SServerInfo.max_clients; SServerInfo.i++) {
            SServerInfo.sd = SServerInfo.client_socket[SServerInfo.i];  
            if (FD_ISSET( SServerInfo.sd , &(SServerInfo.readfds))) {  
                if ((SServerInfo.valread = read( SServerInfo.sd , SServerInfo.buffer, 1024)) == 0) {  
                    close_socket(&SServerInfo);
                } else {
                    SServerInfo.buffer[SServerInfo.valread] = '\0';
                    check_player(&SServerInfo);
                }  
            }  
        }  
    }
    servSocketInfoDestroy(&SServerInfo);
    return (0);  
}