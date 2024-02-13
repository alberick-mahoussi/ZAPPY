/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** run_server
*/

#include "../include/server.h"

static core_game core =
{
    .run_game = true
};

void signalhandler(int signal)
{
    if (signal == SIGINT)
        core.run_game = false;
    else if (signal == SIGPIPE) {
    }
}

int loop_server(server_t *server)
{
    if (fd_select(server) == 84)
        return 84;
    manag_back_fd(server);
    handle_command(server);
    manag_life_players(server);
    return 0;
}

void manag_clock_game(server_t *server)
{
    double time_diff = 0.0;
    server->end_time = clock();
    time_diff = (double)(server->end_time - server->start_time)
    / CLOCKS_PER_SEC;
    if (time_diff >= 1.0 / server->freq) {
        action_on_time(server);
        server->start_time = clock();
    }
}

int run(server_t *server)
{
    srand(time(NULL));
    init_map_game(server);
    server->player_list = calloc(MAX_CLIENT_, sizeof(data_player_t *));
    server->egg_players = calloc(MAX_CLIENT_, sizeof(egg_player_t *));
    if (server_init(server) == 84)
        return 84;
    server->start_time = clock();
    signal(SIGINT, signalhandler);
    signal(SIGPIPE, signalhandler);
    while (core.run_game != false) {
        manag_clock_game(server);
        if (loop_server(server) == 84)
            return 84;
    }
    close(server->network->server_fd);
    return 0;
}
