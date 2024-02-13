/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** forwad
*/

#include "../../../include/server.h"

void response_of_move(server_t *server, data_player_t *player)
{
    get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
    if (server->network->fd_gui != -1 && server->gui_authentifed == true)
        player_position(server, player->id);
}

void forwad_bis_cmd(data_player_t *player, server_t *server)
{
    int x = 0;
    int y = 0;
    switch (player->direction) {
    case RIGHT:
        x = 1;
        break;
    case LEFT:
        x = -1;
        break;
    case UP:
        y = -1;
        break;
    case DOWN:
        y = 1;
        break;
    }
    player->pos_x += x;
    player->pos_y += y;
}

void forwad_cmd(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    int i = player->pos_x;
    int j = player->pos_y;
    forwad_bis_cmd(player, server);
    player->pos_x = player->pos_x >= server->width ? 0 : player->pos_x;
    player->pos_y = player->pos_y >= server->height ? 0 : player->pos_y;
    player->pos_x = player->pos_x < 0 ? server->width - 1 : player->pos_x;
    player->pos_y = player->pos_y < 0 ? server->height - 1 : player->pos_y;
    player->case_on_map = &server->map[player->pos_y][player->pos_x];
    remove_player_in_case(&server->map[j][i], player);
    add_player_in_case(&server->map[player->pos_y][player->pos_x], player);
    response_of_move(server, player);
}

void right_cmd(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1){
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    switch (player->direction) {
        case UP:
            player->direction = RIGHT;
            break;
        case RIGHT:
            player->direction = DOWN;
            break;
        case DOWN:
            player->direction = LEFT;
            break;
        case LEFT:
            player->direction = UP;
            break;
    }
    response_of_move(server, player);
}

void left_cmd(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    switch (player->direction) {
        case UP:
            player->direction = LEFT;
            break;
        case RIGHT:
            player->direction = UP;
            break;
        case DOWN:
            player->direction = RIGHT;
            break;
        case LEFT:
            player->direction = DOWN;
            break;
    }
    response_of_move(server, player);
}
