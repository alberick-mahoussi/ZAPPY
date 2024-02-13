/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** new_client
*/

#include "../include/server.h"

int create_new_player(server_t *server, int fd)
{
    data_player_t *player = malloc(sizeof(data_player_t));
    player->id = server->player_id;
    player->level = 1;
    player->fd = fd;
    player->direction = NONE;
    player->deconnect = false;
    player->died = false;
    player->pos_x = -1;
    player->pos_y = -1;
    player->inventory = malloc(sizeof(inventory_t));
    player->my_team = NULL;
    player->cmd = NULL;
    player->cmd_index = NULL;
    player->case_on_map = NULL;
    init_msg_client(player);
    init_case(player->inventory);
    add_player_list(player, server);
    welcome_client(player);
}

int add_new_client(server_t *server)
{
    int fd = 0;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    if ((fd = accept(server->network->server_fd, (struct sockaddr *)&addr,
    &addr_len)) == -1) {
        perror("accept failed");
        return 84;
    }
    create_new_player(server, fd);
    server->player_id += 1;
    printf("New player connected. File descriptor: %d\n", fd);
    return 0;
}
