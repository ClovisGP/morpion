

#include "../Include/proto.h"


/**
 * This is the loop which run all the client
 * @param socket_info the main clie_socket_info struct of the program
*/
void running_loop(struct clie_socket_info *socket_info)
{
    char buff[MAX];
    int n;

    while (socket_info->is_cli_running) {
        FD_ZERO(&socket_info->rfds);
        FD_SET(socket_info->fd_list[0], &socket_info->rfds);
        FD_SET(socket_info->fd_list[1], &socket_info->rfds);

        int select_activity = select(socket_info->fd_list[1] + 1, &socket_info->rfds, NULL, NULL, NULL);

        if (select_activity == -1){
            perror("select()");
            exit(EXIT_FAILURE);
        }
        for (int index_fd = 0; index_fd < 2; index_fd++) {
            if (FD_ISSET(socket_info->fd_list[index_fd] , &socket_info->rfds)) {
                int valread = read(socket_info->fd_list[index_fd], buff, 1024);

                buff[valread] = '\0';
                if (socket_info->fd_list[index_fd] == socket_info->sockfd)
                    write(1, buff, strlen(buff));
                else {
                    send(socket_info->sockfd, buff, strlen(buff), 0);
                }
                if (strncmp(buff, "QUIT", 4) == 0) {
                    socket_info->is_cli_running = false;
                }
            }
        }
    }
}
 
/**
 * This is the main of the client project
 * @param ac the number of arguments
 * @param ac the array of argument
*/
int main(int ac, char **av)
{
    int tmp_port = find_port(ac, av);
    if (tmp_port == -1) return (-1);
    struct clie_socket_info socket_info = clie_socket_info_construct(tmp_port);
    running_loop(&socket_info);
    close(socket_info.sockfd);
    clie_socket_info_destroy(&socket_info);
    return (0);
}