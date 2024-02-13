/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** place_ressources
*/

#include "../include/server.h"

void place_resource3(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates)
{
    switch (random) {
        case 5:
            if (inventory->phiras > 0 && tile->case_inventory->phiras < 3) {
                inventory->phiras--;
                tile->case_inventory->phiras += 1;
            }
        case 6:
            if (inventory->thystame > 0 &&
            tile->case_inventory->thystame < 3) {
                inventory->thystame--;
                tile->case_inventory->thystame += 1;
            }
    }
}

void place_resource2(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates)
{
    switch (random) {
        case 3:
            if (inventory->sibur > 0 && tile->case_inventory->sibur < 3) {
                inventory->sibur--;
                tile->case_inventory->sibur += 1;
            }
        case 4:
            if (inventory->mendiane > 0
            && tile->case_inventory->mendiane < 3) {
                inventory->mendiane--;
                tile->case_inventory->mendiane += 1;
            }
    }
}

void place_resource1(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates)
{
    switch (random) {
        case 0:
            if (inventory->food > 0 && tile->case_inventory->food < 3) {
                inventory->food--;
                tile->case_inventory->food += 1;
            }
        case 1:
            if (inventory->linemate > 0 &&
            tile->case_inventory->linemate < 3) {
                inventory->linemate--;
                tile->case_inventory->linemate += 1;
            }
        case 2:
            if (inventory->deraumere > 0 &&
            tile->case_inventory->deraumere < 3) {
                inventory->deraumere--;
                tile->case_inventory->deraumere += 1;
            }
    }
}

void place_resources(server_t *server, inventory_t *inventory,
coordinate *coordinates, int size)
{
    int i = 0;

    while (inventory->food > 0 || inventory->linemate > 0 ||
    inventory->deraumere > 0 || inventory->sibur > 0 || inventory->mendiane
    > 0 || inventory->phiras > 0 || inventory->thystame > 0) {
        map_case_t *tile = &server->map[coordinates[i].y][coordinates[i].x];
        int random = rand() % 7;
        place_resource1(random, inventory, tile, coordinates);
        place_resource2(random, inventory, tile, coordinates);
        place_resource3(random, inventory, tile, coordinates);
        i = (i + 1) % size;
    }
}
