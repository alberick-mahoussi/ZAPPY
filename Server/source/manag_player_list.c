/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** Manag_player_list
*/

#include "../include/server.h"

int add_player_list(data_player_t *player, server_t *server)
{
    int i = 0;
    for (i = 0; server->player_list[i] != NULL; i++);
    server->player_list[i] = player;
    return 0;
}
