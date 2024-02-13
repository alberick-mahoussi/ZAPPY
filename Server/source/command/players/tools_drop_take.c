/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tools_drop_take
*/

#include "../../../include/server.h"

void drop_thystame(int x, server_t *serv, data_player_t *player,
inventory_t *inventory)
{
    if (x == 6) {
        if (player->inventory->thystame > 0) {
            take_item_n_inventory(1, player->inventory, "THYSTAME");
            set_item_n_inventory(1, inventory, "THYSTAME"), x = 0;
        }
    }
}

int check_ressource(char *res)
{
    if (res == NULL)
        return -1;
    if (strcasecmp(res, "FOOD") != 0 && strcasecmp(res, "LINEMATE") != 0 &&
    strcasecmp(res, "DERAUMERE") != 0 && strcasecmp(res, "SIBUR") != 0 &&
    strcasecmp(res, "MENDIANE") != 0 && strcasecmp(res, "PHIRAS") != 0 &&
    strcasecmp(res, "THYSTAME") != 0)
        return -1;
    return 0;
}

void take_thystame(int x, server_t *serv, data_player_t *player,
inventory_t *inventory)
{
    if (x == 6) {
        if (player->inventory->thystame > 0) {
            take_item_n_inventory(1, inventory, "THYSTAME");
            set_item_n_inventory(1, player->inventory, "THYSTAME"), x = 0;
        }
    }
}
