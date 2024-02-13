/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** player
*/

#include "../include/server.h"

int count_player(data_player_t **player_list)
{
    if (player_list == NULL)
        return -1;
    int i = -1;
    for (i = 0; player_list[i] != NULL; i++);
    return i;
}

void add_player_in_case(map_case_t *cases, data_player_t *player)
{
    data_player_t **new_player_list = NULL;
    int i = count_player(cases->player_list);
    if (i == -1)
        return;
    if (i >= 1) {
        new_player_list = realloc(cases->player_list, \
        (i + 1) * sizeof(data_player_t *));
        if (new_player_list != NULL) {
            cases->player_list = new_player_list;
            cases->player_list[i] = player;
            cases->player_list[i + 1] = NULL;
        } else {
            perror("realloc player_list");
        }
    } else {
        cases->player_list[i] = player;
        cases->player_list[i + 1] = NULL;
    }
}

void remove_player_in_case(map_case_t *cases, data_player_t *player)
{
    int j = 0;
    int i = -1;
    for (i = 0; cases->player_list[i] != NULL; i++)
        if (cases->player_list[i]->id == player->id)
            break;
    if (i != -1) {
        for (j = i; cases->player_list[j] != NULL; j++) {
            cases->player_list[j] = (cases->player_list[j + 1] != NULL) ?
            cases->player_list[j + 1] : NULL;
        }
    }
}

int new_player(data_player_t *player, server_t *server)
{
    player->pos_x = rand() % server->width;
    player->pos_y = rand() % server->height;
    printf("new player %d %d\n", player->pos_y, player->pos_x);
    player->case_on_map = &server->map[player->pos_y][player->pos_x];
    add_player_in_case(&server->map[player->pos_y][player->pos_x], player);
    player->direction = (dir_t) (rand() % 4 + 1);
    player->life_time = 0;
    player->inventory->food += 10;
    player->forward = 0;
    return 0;
}

int delete_players(data_player_t *player, server_t  *server)
{
    if (player->my_team != NULL)
        player->my_team->nb_players -= 1;
    if (player->case_on_map != NULL) {
        remove_player_in_case(&server->map[player->pos_y][player->pos_x], \
        player);
    } if (player->msg_to_player != NULL)
        free_msg_client(player->msg_to_player);
    if (player->cmd != NULL)
        free(player->cmd);
    free(player->inventory);
    free(player);
}
