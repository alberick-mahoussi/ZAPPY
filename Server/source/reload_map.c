/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** reload_map
*/

#include "../include/server.h"

void clean_map(server_t *server)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < server->height; i++) {
        for (j = 0; j < server->width; j++) {
            init_case(server->map[i][j].case_inventory);
        }
    }
}

int reload_map_bis(server_t *server)
{
    inventory_t *inv = get_inventory(server->height, server->width);
    coordinate coordinates[server->height * server->width];
    int k = 0;
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            coordinates[k].x = i;
            coordinates[k].y = j;
            k++;
        }
    }
    shuffle(coordinates, server->height * server->width);
    place_resources(server, inv, coordinates, server->height * server->width);
    server->map_time = 20;
    free(inv);
    return 0;
}

int reload_map(server_t *server)
{
    if (server->map_time == 0) {
        reload_map_bis(server);
        if (server->network->fd_gui != -1 && server->gui_authentifed == true)
            send_all_content_tile_map(server, "mct");
    }
}
