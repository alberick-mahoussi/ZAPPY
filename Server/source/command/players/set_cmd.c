/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** set_cmd
*/

#include "../../../include/server.h"

const char *item[] = {
"FOOD", "LINEMATE", "DERAUMERE",
"SIBUR", "MENDIANE", "PHIRAS", "THYSTAME",  NULL
};

int take_item_n_inventory(int nb, inventory_t *inventory, char *item)
{
    if (strcmp (item, "FOOD") == 0)
        inventory->food -= nb;
    if (strcmp(item, "LINEMATE") == 0)
        inventory->linemate -= nb;
    if (strcmp(item, "DERAUMERE") == 0)
        inventory->deraumere -= nb;
    if (strcmp(item, "SIBUR") == 0)
        inventory->sibur -= nb;
    if (strcmp (item, "MENDIANE") == 0)
        inventory->mendiane -= nb;
    if (strcmp(item, "PHIRAS") == 0)
        inventory->phiras -= nb;
    if (strcmp(item, "THYSTAME") == 0)
        inventory->thystame -= nb;
    return 0;
}

int set_item_n_inventory(int nb, inventory_t *inventory, char *item)
{
    if (strcmp (item, "FOOD") == 0)
        inventory->food += nb;
    if (strcmp(item, "LINEMATE") == 0)
        inventory->linemate += nb;
    if (strcmp(item, "DERAUMERE") == 0)
        inventory->deraumere += nb;
    if (strcmp(item, "SIBUR") == 0)
        inventory->sibur += nb;
    if (strcmp (item, "MENDIANE") == 0)
        inventory->mendiane += nb;
    if (strcmp(item, "PHIRAS") == 0)
        inventory->phiras += nb;
    if (strcmp(item, "THYSTAME") == 0)
        inventory->thystame += nb;
    return 0;
}

int set_item1(int x, server_t *serv, data_player_t *player)
{
    int z = player->pos_x;
    int y = player->pos_y;
    inventory_t *inventory = serv->map[y][z].case_inventory;
    int i = -1;
    if (x == 0) {
        if (player->inventory->food > 0)
            take_item_n_inventory(1, player->inventory, "FOOD");
            set_item_n_inventory(1, inventory, "FOOD"), x = 0;
    } if (x == 1) {
        if (player->inventory->linemate > 0)
            take_item_n_inventory(1, player->inventory, "LINEMATE");
            set_item_n_inventory(1, inventory, "LINEMATE"), x = 0;
    } if (x == 2) {
        if (player->inventory->deraumere > 0) {
            take_item_n_inventory(1, player->inventory, "DERAUMERE");
            set_item_n_inventory(1, inventory, "DERAUMERE"), x = 0;
        }
    }
    return 0;
}

int set_item2(int x, server_t *serv, data_player_t *player)
{
    int z = player->pos_x;
    int y = player->pos_y;
    inventory_t *inventory = serv->map[y][z].case_inventory;
    int i = -1;
    if (x == 3) {
        if (player->inventory->sibur > 0)
            take_item_n_inventory(1, player->inventory, "SIBUR");
            set_item_n_inventory(1, inventory, "SIBUR"), x = 0;
    } if (x == 4) {
        if (player->inventory->mendiane > 0)
            take_item_n_inventory(1, player->inventory, "MENDIANE");
            set_item_n_inventory(1, inventory, "MENDIANE"), x = 0;
    } if (x == 5) {
        if (player->inventory->phiras > 0) {
            take_item_n_inventory(1, player->inventory, "PHIRAS");
            set_item_n_inventory(1, inventory, "PHIRAS"), x = 0;
        }
    }
    drop_thystame(x, serv, player, inventory);
    return 0;
}

void set_cmd(server_t *server, data_player_t *player)
{
    int j = 0;
    int i = 0;
    char **tab = my_str_to_word_array(player->cmd->cmd_name, " ");

    if (tab == NULL || check_ressource(tab[1]) == -1 ||
    count_array_gab(tab) != 2) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    for (i = 0; item[i] != NULL; i++)
        if (strcasecmp(item[i], tab[1]) == 0)
            break;
    j = (i <= 2) ? set_item1(i, server, player) : set_item2(i, server, player);

    if (j == 0) {
        get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
        server->network->fd_gui != 1 && server->gui_authentifed == true ?
        msg_gui_droping(server, player, i) : 0;
    } else
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
}
