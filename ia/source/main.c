/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** main
*/

#include  "../include/server.h"

void usage(void)
{
    printf("USAGE:\t./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution of ");
    printf("actions\n");
}

int main(int argc, char **argv)
{
    server_t server;
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage();
        return 0;
    } else if (handle_args(argc, argv, &server) == 84) {
        return 84;
    } else {
        run(&server);
    }
    return 0;
}
