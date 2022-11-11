/*
leak memoire de slect
Si un jour quitte
Le client
Voir un systeme qui detecte si tu gagne
opti certain offichage
*/

#include "../Include/proto.h"
     
#define TRUE   1 
#define FALSE  0 
#define PORT 8888

int serverInitialization(struct servSocketInfo *SServerInfo)
{
    //initialise all client_socket[] to 0 so not checked 
    for (SServerInfo->i = 0; SServerInfo->i < SServerInfo->max_clients; SServerInfo->i++) {  
        SServerInfo->client_socket[SServerInfo->i] = 0;  
    }
         
    //create a master socket 
    if( (SServerInfo->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(SServerInfo->master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&(SServerInfo->opt), sizeof(SServerInfo->opt)) < 0 ) {
        perror("setsockopt");  
        exit(EXIT_FAILURE);
    }  

    //type of socket created 
    SServerInfo->address.sin_family = AF_INET;  
    SServerInfo->address.sin_addr.s_addr = INADDR_ANY;  
    SServerInfo->address.sin_port = htons(PORT);  
         
    //bind the socket to localhost port 8888 
    if (bind(SServerInfo->master_socket, (struct sockaddr *)&SServerInfo->address, sizeof(SServerInfo->address)) < 0) {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 2 pending connections for the master socket 
    if (listen(SServerInfo->master_socket, 2) < 0) {
        perror("listen");  
        exit(EXIT_FAILURE);  
    }
         
    //accept the incoming connection 
    SServerInfo->addrlen = sizeof(SServerInfo->address);  
    puts("Waiting for connections ...");
    return (0);
}
     
int main(int argc , char *argv[])  
{
    struct servSocketInfo SServerInfo = servSocketInfoConstruct();     
    //a message 
    char *message = "ECHO Daemon v1.0 \r\n";  
     
    serverInitialization(&SServerInfo);
         
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&(SServerInfo.readfds));  
     
        //add master socket to set 
        FD_SET(SServerInfo.master_socket, &(SServerInfo.readfds));  
        SServerInfo.max_sd = SServerInfo.master_socket;  
             
        //add child sockets to set 
        for (SServerInfo.i = 0; SServerInfo.i < SServerInfo.max_clients; SServerInfo.i++) {  
            //socket descriptor 
            SServerInfo.sd = SServerInfo.client_socket[SServerInfo.i];  
                 
            //if valid socket descriptor then add to read list 
            if(SServerInfo.sd > 0)  
                FD_SET( SServerInfo.sd , &(SServerInfo.readfds));  
                 
            //highest file descriptor number, need it for the select function 
            if(SServerInfo.sd > SServerInfo.max_sd)  
                SServerInfo.max_sd = SServerInfo.sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        SServerInfo.activity = select( SServerInfo.max_sd + 1 , &(SServerInfo.readfds) , NULL , NULL , NULL);  
       
        if ((SServerInfo.activity < 0) && (errno != EINTR)) {  
            printf("select error");  
        }  
             
        new_connection(&SServerInfo);
        
        for (SServerInfo.i = 0; SServerInfo.i < SServerInfo.max_clients; SServerInfo.i++)  
        {  
            SServerInfo.sd = SServerInfo.client_socket[SServerInfo.i];  
                 
            if (FD_ISSET( SServerInfo.sd , &(SServerInfo.readfds)))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((SServerInfo.valread = read( SServerInfo.sd , SServerInfo.buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(SServerInfo.sd , (struct sockaddr*)&(SServerInfo.address) , \
                        (socklen_t*)&(SServerInfo.addrlen));  
                    printf("Host disconnected , ip %s , port %d \n" , \
                          inet_ntoa(SServerInfo.address.sin_addr) , ntohs(SServerInfo.address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( SServerInfo.sd );  
                    SServerInfo.client_socket[SServerInfo.i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    // //set the string terminating NULL byte on the end 
                    // //of the data read 
                    SServerInfo.buffer[SServerInfo.valread] = '\0';
                    
                    // send(SServerInfo.sd , SServerInfo.buffer , strlen(SServerInfo.buffer) , 0 );  
                    check_player(&SServerInfo);
                }  
            }  
        }  
    }  
         
    return 0;  
}