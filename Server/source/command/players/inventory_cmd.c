/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** inventory_cmd
*/

#include "../../../include/server.h"

void inventory_cmd(server_t *server, data_player_t *player)
{
    char msg[4096];
    char **tab = my_str_to_word_array(player->cmd->cmd_name, " ");
    if (count_array_gab(tab ) != 1) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        free_2d(tab);
        return;
    }
    sprintf(msg,
        "[food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d]\n",
        player->inventory->food, player->inventory->linemate,
        player->inventory->deraumere, player->inventory->sibur,
        player->inventory->mendiane, player->inventory->phiras,
        player->inventory->thystame
    );
    get_msg_send(strdup(msg), player->msg_to_player->msg_write);
}
