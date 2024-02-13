/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** team_bis
*/

#include "../include/server.h"

void msg_gui_connection(data_player_t *player, server_t *server);

void add_team_server_bis(server_t *server, int i, data_player_t *player,
teams_t *new_teams)
{
    server->teams_players[i] = new_teams;
    server->teams_players[i + 1] = NULL;
    player->my_team = server->teams_players[i];
    player->life_time = clock();
    new_player_msg(player, server);
    msg_gui_connection(player, server);
}
