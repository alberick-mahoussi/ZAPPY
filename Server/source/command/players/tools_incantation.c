/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tools_incantation
*/

#include "../../../include/server.h"

int count_player_available(int *player_list, int nb_players)
{
    int i = 0;
    int v = 0;
    for (int i = 0; i < nb_players ; i++)
        if (player_list[i] != -1)
            v++;
    return v;
}

int check_level_player(data_player_t **player_list, int level)
{
    int j = 0;
    int i = -1;
    for (j = 0; player_list[j] != NULL; j++)
        if (player_list[j]->level == level) {
            i = j;
            break;
        }
    return i;
}

int *check_n_level_player(data_player_t **player_list, int level,
int nb_players)
{
    int i = 0;
    int n = 0;
    int *list = malloc(sizeof(int) * nb_players);
    if (list == NULL) {
        perror("malloc failed");
        return NULL;
    }
    for (int i = 0; i < nb_players; i++) list[i] = -1;
    for (i = 0; player_list[i] != NULL && n < nb_players; i++) {
        if (player_list[i]->level == level)
            list[n] = i, n++;
    }
    if (n == 0) {
        free(list);
        return NULL;
    }
    return list;
}

void msg_start_incantation_lv_one(server_t *server, data_player_t *player,
data_player_t *player_two)
{
    char msg[50];
    sprintf(msg, "pic %d %d %d %d %d\n", player->pos_x, player->pos_y, \
    player->level, player->id, player_two->id);
    get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}

void msg_end_state_incantation(server_t *server, data_player_t *player,
char *status)
{
    char msg[100];
    sprintf(msg, "pie %d %d %s\n", player->pos_x, player->pos_y, status);
    if (server->gui_authentifed == true && server->network->fd_gui != -1)
        get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}
