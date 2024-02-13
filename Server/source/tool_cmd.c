/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tool_cmd
*/

#include "../include/server.h"

void check_player_cmd(server_t *serv, data_player_t *player)
{
    if (count_msg_tmp(player->msg_to_player->msg_read) > 0
    && player->cmd == NULL) {
        handle_cmd_bis(serv, player);
    } else if (player->cmd != NULL) {
        exec_player_cmd(player, serv);
    }
}

void manag_player_cmd(server_t *serv)
{
    int i = 0;
    for (int i = 0; serv->player_list[i] != NULL; i++) {
        check_player_cmd(serv, serv->player_list[i]);
    }
}

void manage_gui_command(server_t *serv)
{
    if (serv->network->fd_gui != -1 && serv->gui_authentifed == true &&
    (count_msg_tmp(serv->gui_msg->msg_read)) > 0)
        execute_gui_cmd(serv);
}

void manage_player_deconnection(server_t *serv)
{
    if (serv->network->fd_gui == -1) {
        serv->gui_authentifed = false;
        if (serv->gui_msg != NULL)
            free_msg_gui(serv->gui_msg);
    }

    for (int i = 0; serv->player_list[i] != NULL; i++) {
        if (serv->player_list[i]->deconnect == true ||
        serv->player_list[i]->died == true) {
            remove_from_list(serv->player_list[i], serv);
        }
    }
}
