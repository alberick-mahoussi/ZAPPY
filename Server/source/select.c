/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** select
*/

#include "../include/server.h"

int init_select(int fd_max, server_t *server)
{
    fd_set *write_set = &server->network->write_fd;
    fd_set *read_set = &server->network->read_fd;
    if (select(fd_max + 1, read_set, write_set, NULL, NULL) == -1) {
        perror("select not working");
        return 84;
    }
    return 0;
}

int init_descriptor(server_t *server)
{
    int fd_max = server->network->server_fd > server->network->fd_gui ?
    server->network->server_fd : server->network->fd_gui;
    FD_ZERO(&server->network->read_fd);
    FD_ZERO(&server->network->write_fd);
    FD_SET(server->network->server_fd, &server->network->read_fd);
    return fd_max;
}

int fd_select(server_t *server)
{
    int fd_max = init_descriptor(server);
    if (server->network->fd_gui != -1) {
        FD_SET(server->network->fd_gui, &server->network->read_fd);
        FD_SET(server->network->fd_gui, &server->network->write_fd);
    }
    for (int i = 0; server->player_list[i] != NULL; i++) {
        if (server->player_list[i]->fd > 0) {
            FD_SET(server->player_list[i]->fd, &server->network->read_fd);
            FD_SET(server->player_list[i]->fd, &server->network->write_fd);
            fd_max = fd_max < server->player_list[i]->fd ?
            server->player_list[i]->fd : fd_max;
        }
    }
    if (init_select(fd_max, server) == 84)
        return 84;
    return 0;
}

void manag_isset_gui(server_t *server)
{
    if (FD_ISSET(server->network->fd_gui, &server->network->read_fd)) {
        if (server->network->fd_gui != -1 && server->gui_authentifed == true)
            read_message_gui(server->network->fd_gui, server);
    }
    if (FD_ISSET(server->network->fd_gui, &server->network->write_fd))
        if (server->network->fd_gui != -1 && server->gui_authentifed == true)
            send_msg_gui(server);
}

int manag_back_fd(server_t *server)
{
    char *msg_gui = NULL;
    if (FD_ISSET(server->network->server_fd, &server->network->read_fd)) {
        printf("new_client\n"), add_new_client(server);
    }
    manag_isset_gui(server);
    for (int i = 0; server->player_list[i] != NULL; i++) {
        if (FD_ISSET(server->player_list[i]->fd, &server->network->read_fd))
            read_message(server->player_list[i]);
        if (FD_ISSET(server->player_list[i]->fd, &server->network->write_fd))
            send_msg(server->player_list[i]);
    }
    return 0;
}
