/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** player
*/

#include "../../../include/server.h"

void player_position(server_t *server, int id_n)
{
    if (id_n > server->player_id)
        return;
    int i = -1;
    char info[32];
    for (i = 0; server->player_list[i] != NULL; i++)
        if (server->player_list[i]->id == id_n)
            break;
    if (i != -1) {
        sprintf(info, "ppo %d %d %d %d\n", id_n, \
        server->player_list[i]->pos_x, server->player_list[i]->pos_y, \
        server->player_list[i]->direction);
        get_msg_write_gui(strdup(info), &server->gui_msg->msg_write);
    }
}

void player_level(server_t *server, int id_n)
{
    if (id_n > server->player_id)
        return;
    char info[50];
    int i = -1;
    for (i = 0; server->player_list[i] != NULL; i++)
        if (server->player_list[i]->id == id_n)
            break;
    if (i != -1) {
        sprintf(info, "plv %d %d\n", id_n, server->player_list[i]->level);
        get_msg_write_gui(strdup(info), &server->gui_msg->msg_write);
    }
}

void player_inventory(server_t *server, int id_n)
{
    if (id_n > server->player_id)
        return;
    char player[150];
    int i = -1;
    for (i = 0; server->player_list[i] != NULL; i++)
        if (server->player_list[i]->id == id_n)
            break;
    if (i != -1) {
        sprintf(player,"pin %d %d %d %d %d %d %d %d %d %d\n", id_n, \
        server->player_list[id_n]->pos_x, server->player_list[id_n]->pos_y, \
        server->player_list[id_n]->inventory->food, \
        server->player_list[id_n]->inventory->linemate, \
        server->player_list[id_n]->inventory->deraumere, \
        server->player_list[id_n]->inventory->sibur, \
        server->player_list[id_n]->inventory->mendiane, \
        server->player_list[id_n]->inventory->phiras, \
        server->player_list[id_n]->inventory->thystame);
        get_msg_write_gui(strdup(player), &server->gui_msg->msg_write);
    }
}
