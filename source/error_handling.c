/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** error_handling
*/

#include "../include/server.h"

int stock(char *argv)
{
    char *arg_type[] = {
        "-p", "-x", "-y",
        "-c", "-f", "-n",
        NULL
    };

    for (int i = 0; arg_type[i] != NULL; i++) {
        if (strcmp(argv, arg_type[i]) == 0)
            return i;
    }
    return (-1);
}

int check_arg_type_two(char *argv, server_t *server, char **arg)
{
    int j = 0;
    int i = stock(argv);
    switch (i) {
    case 4:
        server->freq = atoi(arg[(string_position(arg, argv) + 1)]);
        break;
    case 5:
        j = manag_teams_name(string_position(arg, argv), arg, server);
        break;
    default:
        printf("bad %s\n", argv);
        j = 1;
    }
    return j;
}

int check_arg_type_one(char *argv, server_t *server, char **arg)
{
    int j = 0;
    int i = stock(argv);
    switch (i) {
    case 0:
        server->port = atoi(arg[(string_position(arg, argv) + 1)]);
        break;
    case 1:
        server->width = atoi(arg[(string_position(arg, argv) + 1)]);
        break;
    case 2:
        server->height = atoi(arg[(string_position(arg, argv) + 1)]);
        break;
    case 3:
        server->nb_players = atoi(arg[(string_position(arg, argv) + 1)]);
        break;
    default:
        check_arg_type_two(argv, server, arg);
    }
    return j;
}

void server_initialise(server_t *server)
{
    server->port = 0;
    server->freq = 0;
    server->nb_players = 0;
    server->height = 0;
    server->width = 0;
    server->teams_players = NULL;
}

int handle_args(int argc, char **argv, server_t *server)
{
    int i = 1;
    server_initialise(server);
    while (i < argc) {
        switch (check_arg_type_one(argv[i], server, argv)) {
            case 1:
                error_message("Bad params\n");
                return 84;
                break;
            case 0:
                break;
        }
        i += 2;
    }
    printf("server %d %d %d %d %d\n", server->port, server->width, server->height, server->freq, server->nb_players);
    printf("server %s %s\n", server->teams_players[0]->name_teams, server->teams_players[2]->name_teams);
    if (check_good_value_server(server) == 84)
        return 84;
    return 0;
}
