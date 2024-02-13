/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** init_server
*/

#include "../include/server.h"

int bind_server(server_t *server)
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server->network->server_fd, (struct sockaddr *)&server_addr,
    sizeof(server_addr)) == -1) {
        return 84;
    }
    return 0; 
}


int server_init(server_t *server)
{
    server->network = malloc(sizeof(network_t));
    server->network->fd_client = -1;
    if ((server->network->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "socket error");
        return 84;
    }
    if (bind_server(server) == 84) {
        fprintf(stderr, "bind failed");
        return 84;
    }
    if (listen(server->network->server_fd, 4096) == -1) {
        fprintf(stderr, "listen fail");
    }
    return 0;
}
