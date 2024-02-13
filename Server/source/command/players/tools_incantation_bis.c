/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tools_incantation_bis
*/

#include "../../../include/server.h"

void msg_start_incantation_lv_n(server_t *server, data_player_t *player,
data_player_t **players, int players_need)
{
    int *pos_player = check_n_level_player(players, 2, 2);
    int i = 0;
    char msg[150];
    msg[0] = '\0';
    sprintf(msg, "pic %d %d %d %d ", player->pos_x, player->pos_y,
            player->level, player->id);

    for (i = 0; i <= players_need - 2; i++) {
        char player_id[10];
        sprintf(player_id, "%d ", players[pos_player[i]]->id);
        strcat(msg, player_id);
    }

    char last_player_id[10];
    sprintf(last_player_id, "%d\n", players[pos_player[i + 1]]->id);
    strcat(msg, last_player_id);
    get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}

void take_and_drop_lv_three(int *list, data_player_t *player, \
data_player_t **list_player, inventory_t *inventory_case)
{
    player->level += 1;
    inventory_case->linemate -= 1;
    inventory_case->deraumere -= 1;
    inventory_case->sibur -= 1;
    for (int i = 0; i < 2; i++) {
        list_player[list[i]]->level++;
    }
}
