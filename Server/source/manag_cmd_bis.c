/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** manag_cmd_bis
*/

#include "../include/server.h"

void exec_player_cmd(data_player_t *player, server_t *server)
{
    if (player->cmd == NULL) {
        printf("No command\n");
        return;
    }
    if (player->cmd->time_cycle == 0) {
        printf("I can do command\n");
        player->cmd->cmd(server, player);
        free(player->cmd->cmd_name);
        free(player->cmd);
        player->cmd = NULL;
        delete_msg_cmd(player->cmd_index, player->msg_to_player->msg_read);
        player->cmd_index = NULL;
    }
}
