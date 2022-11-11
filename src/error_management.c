#include "../Include/proto.h"

int check_arg(int ac, char **av)
{
    if (ac != 2) {
        write(2, "ERROR: this program only takes two arguments are allowed\n", 38);
        write(2, "USAGE: ./theGame port\n", 25);
        write(2, "\t  port is the port number on which the ", 40);
        write(2, "server socket listens\n", 22);
        return (ERROR_CODE);
    } else if (str_is_digit(av[1]) == ERROR_CODE) {
        write(2, "ERROR: PORT is unavailable\n", 27);
        return (ERROR_CODE);
    }
    return (SUCCESS_CODE);
}

int str_is_digit(char *str)
{
    for(int comp = 0; str[comp] != '\0'; comp++) {
        if (str[comp] < 48 || str[comp] > 57)
            return (ERROR_CODE);
    }
    return (SUCCESS_CODE);
}