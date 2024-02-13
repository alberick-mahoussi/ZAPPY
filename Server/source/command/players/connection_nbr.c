/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** connection_nbr
*/

#include "../../../include/server.h"

void connect_nbr_cmd(server_t *server, data_player_t *player)
{
    char buffer[5];
    sprintf(buffer, "%d\n", server->nb_players - player->my_team->nb_players);
    get_msg_send(strdup(buffer), player->msg_to_player->msg_write);
}
