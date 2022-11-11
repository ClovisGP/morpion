#include "../Include/proto.h"

void new_connection(struct servSocketInfo *SServerInfo)
{
    if (FD_ISSET(SServerInfo->master_socket, &(SServerInfo->readfds))) {  
        if ((SServerInfo->new_socket = accept(SServerInfo->master_socket, 
            (struct sockaddr *)&(SServerInfo->address), (socklen_t*)&(SServerInfo->addrlen)))<0)  
        {
            perror("accept");  
            exit(EXIT_FAILURE);  
        }  
        
        player_assign(SServerInfo);
                
        //add new socket to array of sockets 
        for (SServerInfo->i = 0; SServerInfo->i < SServerInfo->max_clients; SServerInfo->i++) {  
            //if position is empty 
            if(SServerInfo->client_socket[SServerInfo->i] == 0) { 
                SServerInfo->client_socket[SServerInfo->i] = SServerInfo->new_socket;  
                printf("Adding to list of sockets as %d\n" , SServerInfo->i);        
                break;  
            }  
        }  
    }  
}


int player_assign(struct servSocketInfo *SServerInfo)
{
    printf("New connection , socket fd is %d , ip is : %s , port : %d \
        \n" , SServerInfo->new_socket , inet_ntoa(SServerInfo->address.sin_addr) , ntohs \
        (SServerInfo->address.sin_port)); 
    if (SServerInfo->x_player == 0) {
        
        SServerInfo->x_player = SServerInfo->new_socket;
        if(send(SServerInfo->new_socket, WELCOMEMESSAGEX, strlen(WELCOMEMESSAGEX), 0) != strlen(WELCOMEMESSAGEX)) {
            perror("send");
            return (-1);
        }
        puts("Welcome message sent successfully for player x");  
        return (0);
    } else if (SServerInfo->y_player == 0) {
        SServerInfo->y_player = SServerInfo->new_socket;
        if(send(SServerInfo->new_socket, WELCOMEMESSAGEO, strlen(WELCOMEMESSAGEO), 0) != strlen(WELCOMEMESSAGEO)) {
            perror("send");
            return (-1);
        }
        puts("Welcome message sent successfully for player o");  
        return (1);
    }
    if(send(SServerInfo->new_socket, WELCOMEMESSAGENO, strlen(WELCOMEMESSAGENO), 0) != strlen(WELCOMEMESSAGENO)) {
        perror("send");
        return (-1);
    }
    puts("Welcome message sent successfully for another player");  
    return (2);
}