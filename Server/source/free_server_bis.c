/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** free_server_bis
*/

#include "../include/server.h"

void free_teams(teams_t *team);

void free_player(data_player_t *player)
{
    free(player->inventory);
    free_msg_client(player->msg_to_player);
    player->cmd != NULL ? free(player->cmd) : 0;
    free(player);
}

void free_map(map_case_t **map, int x, int y)
{
    if (map == NULL)
        return;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            (map[i][j].player_list != NULL) ? free(map[i][j].player_list) : 0;
            free(map[i][j].case_inventory);
        }
    }
    free(map);
}

void free_server2(server_t *server)
{
    for (int i = 0; server->teams_players[i] != NULL; ++i)
        free_teams(server->teams_players[i]);
}

void free_eggs(server_t *server)
{
    for (int i = 0; server->egg_players[i] != NULL; ++i) {
        if (server->egg_players[i] != NULL)
            free(server->egg_players[i]);
    }
    free(server->egg_players);
}
