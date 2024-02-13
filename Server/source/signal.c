/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** signal
*/

#include "../include/server.h"

void handle_signal(int signal)
{
    printf("Déconnexion...\n");
}

int welcome_client(data_player_t *player)
{
    if (write(player->fd, "Welcome\n", sizeof("Welcome\n")) == -1)
        perror("write message new client");
    return 0;
}

void tool_for_remove(server_t *server, int i)
{
    for (int j = i; server->player_list[j] != NULL; j++) {
        server->player_list[j] = server->player_list[j + 1] != NULL ?
        server->player_list[j + 1] : NULL;
    }
}

void remove_from_list(data_player_t *player, server_t *server)
{
    data_player_t *players = NULL;
    for (int i = 0; server->player_list[i] != NULL; i++) {
        if (server->player_list[i]->id == player->id) {
            players = server->player_list[i];
            tool_for_remove(server, i);
            delete_players(players, server);
        }
    }
}
