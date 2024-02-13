/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** free_server
*/

#include "../include/server.h"

void free_msg_client(msg_t *msg_to_player)
{
    if (msg_to_player == NULL)
        return;
    if (msg_to_player->msg_read != NULL) {
        for (int i = 0; msg_to_player->msg_read[i] != NULL; i++)
            free(msg_to_player->msg_read[i]);
        free(msg_to_player->msg_read);
    }
    if (msg_to_player->msg_write != NULL) {
        for (int i = 0; msg_to_player->msg_write[i] != NULL; i++)
            free(msg_to_player->msg_write[i]);
        free(msg_to_player->msg_write);
    }
    free(msg_to_player);
}

void free_teams(teams_t *team)
{
    if (team != NULL) {
        if (team->name_teams != NULL)
            free(team->name_teams);
        free(team);
    }
}

void free_player_list(data_player_t **players)
{
    if (players == NULL)
        return;
    for (int i = 0; players[i] != NULL; i++)
        free_player(players[i]);
    free(players);
}

void free_msg_gui(ms_gui_t *gui_msg)
{
    if (gui_msg == NULL)
        return;
    if (gui_msg->msg_read != NULL) {
        for (int i = 0; gui_msg->msg_read[i] != NULL; i++)
            free(gui_msg->msg_read[i]);
        free(gui_msg->msg_read);
    }
    if (gui_msg->msg_write != NULL) {
        for (int i = 0; gui_msg->msg_write[i] != NULL; i++)
            free(gui_msg->msg_write[i]);
        free(gui_msg->msg_write);
    }
    free(gui_msg);
}

void free_server(server_t *server)
{
    if (server != NULL) {
        if (server->network != NULL)
            free(server->network);
        if (server->teams_players != NULL) {
            free_server2(server);
            free(server->teams_players);
        }
        if (server->map != NULL)
            free_map(server->map, server->height, server->width);
        if (server->player_list != NULL)
            free_player_list(server->player_list);
        if (server->gui_msg != NULL)
            free_msg_gui(server->gui_msg);
        if (server->egg_players != NULL)
            free_eggs(server);
    }
}
