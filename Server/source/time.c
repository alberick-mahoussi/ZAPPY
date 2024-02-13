/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** time
*/

#include "../include/server.h"

void time_player_cmd(data_player_t *player)
{
    if (player->my_team != NULL)
        player->life_time < 126 ? player->life_time += 1 : 0;

    if (player->cmd != NULL) {
        if (player->cmd->time_cycle > 0)
            player->cmd->time_cycle -= 1;
    }
}

void action_on_time(server_t *serv)
{
    if (serv->map_time > 0)
        serv->map_time -= 1;
    for (int i = 0; serv->player_list[i] != NULL; i++)
        time_player_cmd(serv->player_list[i]);
}
