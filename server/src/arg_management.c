#include "../Include/proto.h"

/**
 * This function check and search the port argument
 * @param ac the number of arguments
 * @param ac the array of argument
*/
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

/**
 * This function check and search the size argument
 * @param ac the number of arguments
 * @param ac the array of argument
*/
int find_board_size(int ac, char *av[])
{
    char *delim = "-";

    for(int index = 0; index < ac; index++) {
        if (strcmp(strtok(av[index], delim), "size") == 0) {
            char *raw_size = strtok(NULL, delim);
            int size = atoi(raw_size);

            if (size >= 10 || size < 3) {
                return (3);
            }
            return (size);
        }
    }
    return (3);
}