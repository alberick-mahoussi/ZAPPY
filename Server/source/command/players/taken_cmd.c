/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** taken_cmd
*/

#include "../../../include/server.h"

const char *ing[] = {
    "FOOD", "LINEMATE", "DERAUMERE",
    "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME", NULL
};

int take_one(int x, server_t *serv, data_player_t *player)
{
    int z = player->pos_x;
    int y = player->pos_y;
    inventory_t *inventory = serv->map[y][z].case_inventory;
    int i = -1;
    if (x == 0) {
        if (inventory->food > 0)
            take_item_n_inventory(1, inventory, "FOOD");
            set_item_n_inventory(1, player->inventory, "FOOD"), x = 0;
    } if (x == 1) {
        if (inventory->linemate > 0)
            take_item_n_inventory(1, inventory, "LINEMATE");
            set_item_n_inventory(1, player->inventory, "LINEMATE"), x = 0;
    } if (x == 2) {
        if (inventory->deraumere > 0) {
            take_item_n_inventory(1, inventory, "DERAUMERE");
            set_item_n_inventory(1, player->inventory, "DERAUMERE"), x = 0;
        }
    }
    return x;
}

int take_two(int x, server_t *serv, data_player_t *player)
{
    int z = player->pos_x;
    int y = player->pos_y;
    inventory_t *inventory = serv->map[y][z].case_inventory;
    int i = -1;
    if (x == 3) {
        if (inventory->sibur > 0)
            take_item_n_inventory(1, inventory, "SIBUR");
            set_item_n_inventory(1, player->inventory, "SIBUR"), x = 0;
    } if (x == 4) {
        if (player->inventory->mendiane > 0)
            take_item_n_inventory(1, inventory, "MENDIANE");
            set_item_n_inventory(1, player->inventory, "MENDIANE"), x = 0;
    } if (x == 5) {
        if (player->inventory->phiras > 0) {
            take_item_n_inventory(1, inventory, "PHIRAS");
            set_item_n_inventory(1, player->inventory, "PHIRAS"), x = 0;
        }
    }
    take_thystame(x, serv, player, inventory);
    return x;
}

void msg_gui_droping(server_t *server, data_player_t *player, int i)
{
    char msg[50];
    sprintf(msg, "pdr %d %d\n", player->id, (ressource_t)i);
    get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}

void msg_gui_collect(server_t *server, data_player_t *player, int i)
{
    char msg[50];
    sprintf(msg, "pgt %d %d\n", player->id, (ressource_t)i);
    get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
}

void take_cmd(server_t *server, data_player_t *player)
{
    int j = 0;
    int i = 0;
    char **tab = my_str_to_word_array(player->cmd->cmd_name, " ");
    if (tab == NULL || check_ressource(tab[1]) == -1 ||
    count_array_gab(tab) != 2) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    for (i = 0; ing[i] != NULL; i++)
        if (strcasecmp(ing[i], tab[1]) == 0)
            break;
    j = (i <= 2) ? take_one(i, server, player) : take_two(i, server, player);
    if (j == 0) {
        get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
        server->network->fd_gui != 1 && server->gui_authentifed == true ?
        msg_gui_collect(server, player, i) : 0;
    } else
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
    free_2d(tab);
}
