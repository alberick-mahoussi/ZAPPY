/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tool_map
*/

#include "../../../include/server.h"

char *get_content_tile(server_t *server, int height, int widht)
{
    char msg[1024];
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n", widht, height, \
    server->map[height][widht].case_inventory->food, \
    server->map[height][widht].case_inventory->linemate, \
    server->map[height][widht].case_inventory->deraumere, \
    server->map[height][widht].case_inventory->sibur, \
    server->map[height][widht].case_inventory->mendiane, \
    server->map[height][widht].case_inventory->phiras, \
    server->map[height][widht].case_inventory->thystame);
    return strdup(msg);
}

void print_tile_content(server_t *server, int height, int widht)
{
    char msg[1024];
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n", widht, height, \
    server->map[height][widht].case_inventory->food, \
    server->map[height][widht].case_inventory->linemate, \
    server->map[height][widht].case_inventory->deraumere, \
    server->map[height][widht].case_inventory->sibur, \
    server->map[height][widht].case_inventory->mendiane, \
    server->map[height][widht].case_inventory->phiras, \
    server->map[height][widht].case_inventory->thystame);
    get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}
