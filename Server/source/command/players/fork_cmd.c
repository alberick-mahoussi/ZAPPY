/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** fork
*/

#include "../../../include/server.h"

void fork_cmd(server_t *server, data_player_t *player)
{
    player->my_team->nb_players += 1;
    get_msg_send(strdup("ok\n"), server->gui_msg->msg_write);
}
