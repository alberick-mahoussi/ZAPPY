/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** other_function_for_error
*/

#include "../include/server.h"
#include "string.h"

int error_message(char *msg)
{
    fprintf(stdout, "Error: %s\n", msg);
    return (84);
}

int manag_teams_name(int i, char **argv, server_t * server)
{
    int j = 0;
    int y = 0;
    for (j = i + 1; argv[j] != NULL && argv[j][0] != '-'; j++, y++);
    if (y == 0) {
        printf("No name");
        error_message("Need name after flags -n\n");
    } else {
        server->teams_players = malloc(sizeof(teams_t *) * (y + 1));
        y = 0;
        for (j = i + 1; argv[j] != NULL && argv[j][0] != '-'; j++, y++) {
            server->teams_players[y] = malloc(sizeof(teams_t));
            //server->teams_players[j]->nb_players = server->nb_players;
            server->teams_players[y]->name_teams = strdup(argv[j]);
        }
        server->teams_players[j] = NULL;
    }
    return (j - 2);
}

int check_good_value_server(server_t *server)
{
    if (server->port  == 0 || server->freq == 0 || server->nb_players == 0)
        usage(), error_message("Need one or more values");
    return 0;
}

int string_position(char **tab, char *str)
{
    int i = 0;
    for (i = 0; tab[i] != NULL; i++)
        if (strcmp(tab[i], str) == 0)
            return i;
    return -1;
}