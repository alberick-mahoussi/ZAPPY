/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** handle_player_life
*/

#include "../include/server.h"

void manag_life_player_bis(data_player_t *player, server_t *server)
{
    char msg[50];
    char druid[50];
    sprintf(msg, "dead\n");
    sprintf(druid, "pdi %d\n", player->id);

    if (player->my_team == NULL)
        return;

    if (player->life_time == 126) {
        if (player->inventory->food > 0) {
            player->inventory->food -= 1;
            player->life_time = 0;
        } else {
            player->died = true;
            get_msg_send(strdup(msg), player->msg_to_player->msg_write);
            server->network->fd_gui != -1 && server->gui_authentifed == true ?
            get_msg_write_gui(strdup(druid), &server->gui_msg->msg_write) : 0;
        }
    }
}

void manag_life_players(server_t *server)
{
    if (server->player_list == NULL)
        return;
    for (int i = 0; server->player_list[i] != NULL; i++) {
        if (server->player_list[i]->my_team != NULL)
            manag_life_player_bis(server->player_list[i], server);
    }
}
