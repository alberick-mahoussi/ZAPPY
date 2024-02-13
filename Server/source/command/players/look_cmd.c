/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** look_cmd
*/

#include "../../../include/server.h"

void look_up(server_t *server, data_player_t *player)
{
    int y = player->pos_y - 1;
    int x = player->pos_x - 1;
    if (x < 0 && y < 0) {
        look_up_bis(player, server, server->height - 1, server->width - 1);
        return;
    }
    if (x < 0) {
        look_up_bis(player, server, y, server->width - 1);
        return;
    }
    if (y < 0) {
        look_up_bis(player ,server, server->height - 1, x);
        return;
    }
    look_up_bis(player, server, y, x);
}

void look_down(server_t *server, data_player_t *player)
{
    int y = player->pos_y + 1;
    int x = player->pos_x + 1;
    if (x >= server->width && y >= server->height) {
        look_down_bis(player, server, 0, 0);
        return;
    }
    if (x >= server->width) {
        look_down_bis(player, server, y, 0);
        return;
    }
    if (y >= server->height) {
        look_down_bis(player, server, 0, x);
        return;
    }
    look_down_bis(player, server, y, x);
}

void look_left(server_t *server, data_player_t *player)
{
    int y = player->pos_y + 1;
    int x = player->pos_x - 1;
    if (x < 0 && y >= server->height) {
        look_left_bis(player, server, 0, server->width - 1);
        return;
    }
    if (x < 0) {
        look_left_bis(player, server, y, server->width - 1);
        return;
    }
    if (y >= server->height) {
        look_left_bis(player, server, 0, x);
        return;
    }
    look_left_bis(player, server, y, x);
}

void look_right(server_t *server, data_player_t *player)
{
    int y = player->pos_y - 1;
    int x = player->pos_x + 1;
    if (x >= server->width && y < 0) {
        look_right_bis(player, server, server->height - 1, 0);
        return;
    }
    if (y < 0) {
        look_right_bis(player, server, server->height -1, x);
        return;
    }
    if (x >= server->width) {
        look_right_bis(player, server, y, 0);
        return;
    }
    look_right_bis(player, server, y, x);
}

void look_cmd(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1) {
        get_msg_send("ko\n", player->msg_to_player->msg_write);
        return;
    }
    switch (player->direction) {
        case UP:
            look_up(server, player);
            break;
        case DOWN:
            look_down(server, player);
            break;
        case LEFT:
            look_left(server, player);
            break;
        case RIGHT:
            look_right(server, player);
            break;
    }
}
