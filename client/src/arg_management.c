#include "../Include/proto.h"

int find_port(int ac, char *av[])
{
    char *delim = "-";

    for(int index = 0; index < ac; index++) {
        if (strcmp(strtok(av[index], delim), "port") == 0) {
            char *raw_port = strtok(NULL, delim);
            int port = atoi(raw_port);

            if (port >= 9999 || port < 1) {
                printf("Error: the port number is unavailable. It must be between 1 and 9999.");
                return (-1);
            }
            return (port);
        }
    }
    printf("Error: the port number is unavailable.");
    return (-1);
}