/*
** EPITECH PROJECT, 2023
** ù
** File description:
** build_map_game
*/

#include "../include/server.h"

void init_case(inventory_t *inv)
{
    inv->food = 0;
    inv->sibur = 0;
    inv->phiras = 0;
    inv->deraumere = 0;
    inv->thystame = 0;
    inv->linemate = 0;
    inv->mendiane = 0;
}

inventory_t *get_inventory(int height, int width)
{
    inventory_t *inv = malloc(sizeof(inventory_t));
    inv->food = height * width * FOOD_DENSITY;
    inv->sibur = height * width * SIBUR_DENSITY;
    inv->phiras = height * width * PHIRAS_DENSITY;
    inv->deraumere = height * width * DERAUMERE_DENSITY;
    inv->thystame = height * width * THYSTAME_DENSITY;
    inv->linemate = height * width * LINEMATE_DENSITY;
    inv->mendiane = height * width * MENDIANE_DENSITY;
    return inv;
}

void place_fruits_on_map(server_t *server, inventory_t *inventory)
{
    if (inventory->food > 0) {
        int food_x = rand() % server->width;
        int food_y = rand() % server->height;
        server->map[food_y][food_x].food += 1;
        inventory->food--;
    }
    if (inventory->sibur > 0) {
        int sibur_x = rand() % server->width;
        int sibur_y = rand() % server->height;
        server->map[sibur_y][sibur_x].sibur += 1;
        inventory->sibur--;
    }
    if (inventory->phiras > 0) {
        int phiras_x = rand() % server->width;
        int phiras_y = rand() % server->height;
        server->map[phiras_y][phiras_x].phiras += 1;
        inventory->phiras--;
    }
    if (inventory->deraumere > 0) {
        int deraumere_x = rand() % server->width;
        int deraumere_y = rand() % server->height;
        server->map[deraumere_y][deraumere_x].deraumere += 1;
        inventory->deraumere--;
    }
    if (inventory->thystame > 0) {
        int thystame_x = rand() % server->width;
        int thystame_y = rand() % server->height;
        server->map[thystame_y][thystame_y].thystame += 1;
        inventory->thystame--;
    }
    if (inventory->linemate > 0) {
        int linemate_x = rand() % server->width;
        int linemate_y = rand() % server->height;
        server->map[linemate_y][linemate_x].linemate += 1;
        inventory->linemate--;
    }
    if (inventory->mendiane > 0) {
        int mendiane_x = rand() % server->width;
        int mendiane_y = rand() % server->height;
        server->map[mendiane_y][mendiane_x].mendiane += 1;
        inventory->mendiane--;
    }
}

int init_map_game(server_t *server)
{
    int i = 0;
    server->map = malloc(sizeof(inventory_t *) * (server->height + 1));
    if (server->map == NULL)
        fprintf(stdout, "Couldn't allocate memory for inventory\n");
    for (i = 0; i < server->height; i++) {
        server->map[i] = malloc(sizeof(inventory_t) * (server->width + 1));
        if (server->map[i] == NULL) {
           fprintf(stdout, "Couldn't allocate memory for inventory in case\n");
           return 84;
        }
        for (int j = 0; j < server->width; j++) {
            init_case(&server->map[i][j]);
        }
    }
    inventory_t *inv = get_inventory(server->height, server->width);
    //printf ("%d %d %d %d %d %d %d\n", inv->food, inv->sibur, inv->phiras, inv->deraumere, inv->thystame, inv->linemate, inv->mendiane);
    while (inv->food != 0 && inv->sibur != 0 && inv->phiras != 0 && 
    inv->deraumere != 0 && inv->thystame != 0 && inv->linemate != 0 
    && inv->mendiane != 0) place_fruits_on_map(server, inv);
    //printf ("%d %d %d %d %d %d %d\n", server->map[0][0].food, server->map[0][0].sibur, server->map[0][0].phiras, server->map[0][0].deraumere, server->map[0][0].thystame, server->map[0][0].linemate, server->map[0][0].mendiane);
    return 0;
}
