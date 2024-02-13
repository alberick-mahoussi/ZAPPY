/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** build_map_game
*/

#include "../include/server.h"

void shuffle(coordinate *array, int size)
{
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        coordinate temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

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

int init_cases(server_t *server)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < server->height; i++) {
        server->map[i] = malloc(sizeof(map_case_t) * (server->width + 1));
        if (server->map[i] == NULL) {
            fprintf(stdout, "Couldn't allocate memory for map in case\n");
            return 84;
        }
        for (j = 0; j < server->width; j++) {
            server->map[i][j].player_list = calloc(2, sizeof(data_player_t *));
            server->map[i][j].case_inventory = malloc(sizeof(inventory_t));
            init_case(server->map[i][j].case_inventory);
        }
    }
    server->map[i] = NULL;
    return 0;
}

int init_map_game(server_t *server)
{
    server->map = malloc(sizeof(map_case_t *) * (server->height + 1));
    if (server->map == NULL) {
        fprintf(stdout, "Couldn't allocate memory for map\n");
        return 84;
    }
    init_cases(server);
    inventory_t *inv = get_inventory(server->height, server->width);
    coordinate coordinates[server->height * server->width];
    for (int i = 0, k = 0; i < server->height; i++) {
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
