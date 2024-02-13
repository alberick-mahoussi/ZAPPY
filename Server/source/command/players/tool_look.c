/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tool_look
*/

#include "../../../include/server.h"

char *get_all_ressource(ressource_t ressource, int nb)
{
    char item[4096];
    item[0] = '\0';
    if (nb == 0)
        return "";
    for (int i = 0; i < nb; i++) {
        if (i < nb - 1) {
            strcat(item, name_of_ressource(ressource));
            strcat(item, " ");
        } else
            strcat(item, name_of_ressource(ressource));
    }
    return strdup(item);
}

char *inventory_case_string(inventory_t *inventory)
{
    char *msg = malloc(sizeof(char) * 1000);
    msg[0] = '\0';
    strcat(msg, get_all_ressource(FOOD, inventory->food));
    inventory_case_bis(msg, inventory);
    return msg;
}

char *get_tile_contents(map_case_t *cases, int players)
{
    char *tile_contents = malloc(sizeof(char) * 4096);
    tile_contents[0] = '\0';
    bool found_players = false;
    for (int i = 0; i < players; i++) {
        found_players = true;
        if (i < players - 1)
            strcat(tile_contents, "player ");
        else
            strcat(tile_contents, "player");
    }
    if (check_inventory_case(cases->case_inventory) == true) {
        found_players == true ? strcat(tile_contents, " ") : 0;
        strcat(tile_contents, inventory_case_string(cases->case_inventory));
    }

    return tile_contents;
}

int count_player_in_case(map_case_t *case_map)
{
    int i = 0;
    if (case_map == NULL)
        return 0;
    for (i = 0; case_map->player_list[i] != NULL; i++);
    return i;
}

map_case_t *check_case_look(server_t *server, int y, int x)
{
    if (y < 0)
        y = server->height + y;
    if (x < 0)
        x = server->width + x;
    printf ("case_look %d %d\n", y, x);
    if ((y >= 0 && y < server->height) && (x >= 0 && x < server->width))
        return &(server->map[y][x]);
    return NULL;
}
