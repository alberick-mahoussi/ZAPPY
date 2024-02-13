/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include "lib.h"

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    typedef struct teams {
        char *name_teams;
        int nb_players;
    }teams_t;

    typedef struct network {
        int server_fd;
        int fd_client;
    } network_t;

    typedef struct inventory_s {
        int food;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
    } inventory_t;

    enum ressource {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
    };

    typedef struct data_player_s {
        int id;
        int level;
        int pos_x;
        int pos_y;
        enum ressource inventory;
    } data_player_t;

    typedef struct list_player {
        data_player_t *player;
    } list_player_t;

    typedef struct server {
        int port;
        int freq;
        int nb_players;
        int height;
        int width;
        network_t *network;
        teams_t **teams_players;
        inventory_t **map;
        bool run;
        list_player_t *player_list;
    }server_t;


int error_message(char *msg);
int manag_teams_name(int i, char **argv, server_t * server);
void usage(void);
int check_good_value_server(server_t *server);
int handle_args(int argc, char **argv, server_t *server);
int string_position(char **tab, char *str);
int server_init(server_t *server);
int init_map_game(server_t *server);
#endif /* !SERVER_H_ */
