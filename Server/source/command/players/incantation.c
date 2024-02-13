/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** incantation
*/

#include "../../../include/server.h"

void level_up_two_bis(server_t *server, data_player_t *player,
int pos_player)
{
    char msg[50];
    int x = player->pos_x;
    int y = player->pos_y;
    player->level += 1;
    server->map[y][x].case_inventory->linemate -= 1;
    server->map[y][x].player_list[pos_player]->level += 1;
    sprintf(msg, "Current level: %d", player->level);
    get_msg_send(strdup("Elevation underway\n"),
    player->msg_to_player->msg_write);
    get_msg_send(strdup(msg), player->msg_to_player->msg_write);
    msg_end_state_incantation(server, player, "ok");
}

void level_up_two(server_t *server, data_player_t *player)
{
    int x = player->pos_x;
    int y = player->pos_y;
    int pos_player = check_level_player(server->map[y][x].player_list, 1);

    if (server->gui_authentifed == true && server->network->fd_gui != -1) {
        msg_start_incantation_lv_one(server, player, \
        server->map[y][x].player_list[pos_player]);
    }
    if (server->map[y][x].case_inventory->linemate < 1 ||
    count_player_list(server->map[y][x].player_list) < 2 ||
    pos_player == -1) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        msg_end_state_incantation(server, player, "ko");
        return;
    }
    level_up_two_bis(server, player, pos_player);
}

void level_up_three_bis(int *list, server_t *server,
data_player_t *player)
{
    int x = player->pos_x;
    int y = player->pos_y;
    char msg[50];
    take_and_drop_lv_three(list, player, server->map[y][x].player_list, \
    server->map[y][x].case_inventory);
    sprintf(msg, "Current level: %d", player->level);
    get_msg_send(strdup("Elevation underway\n"),
    player->msg_to_player->msg_write);
    get_msg_send(strdup(msg), player->msg_to_player->msg_write);
    msg_end_state_incantation(server, player, "ok");
}

void level_up_three(server_t *server, data_player_t *player)
{
    int x = player->pos_x;
    int y = player->pos_y;
    int *list = check_n_level_player(server->map[y][x].player_list, 2, 2);
    int player_nb = count_player_available(list, 2);
    inventory_t * inventory = server->map[y][x].case_inventory;
    if (server->gui_authentifed == true && server->network->fd_gui != -1) {
        msg_start_incantation_lv_n(server, player, \
        server->map[y][x].player_list, 2);
    }
    if (inventory->linemate < 1 || inventory->deraumere || inventory->sibur < 1
    || count_player_list(server->map[y][x].player_list) < 2 || player_nb < 2) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        msg_end_state_incantation(server, player, "ko");
        return;
    }
    level_up_three_bis(list, server, player);
}

void incantation_cmd(server_t *server, data_player_t *player)
{
    char **tab = my_str_to_word_array(player->cmd->cmd_name, " ");
    if (count_array_gab(tab ) != 1) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        free_2d(tab);
        return;
    }
    switch (player->level) {
    case 1:
        level_up_two(server, player);
        break;
    case 2:
        level_up_three(server, player);
        break;
    }
    free_2d(tab);
}
