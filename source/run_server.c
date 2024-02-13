/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** run_server
*/

#include "../include/server.h"

int run(server_t *server)
{
    srand(time(NULL));
    init_map_game(server);
    server->run = true;
    /*if (server_init(server) == 84)
        return 84;
    while (server->run != false) {
    }*/ 
}