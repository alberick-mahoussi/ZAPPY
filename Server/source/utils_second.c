/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** utils_second
*/

#include "../include/server.h"

int count_egg_on_case(server_t *server, map_case_t *cases)
{
    if (server->egg_players == NULL || server->egg_players[0] == NULL)
        return 0;
    int count = 0;

    for (int i = 0; server->egg_players[i] != NULL; i++)
        if (server->egg_players[i]->case_on_map == cases)
            count++;
    return count;
}
