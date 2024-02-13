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
    #define MAX_CLIENT_ 4096
    
    typedef struct server server_t;
    typedef struct data_player_s data_player_t;
    typedef void (*cmd_t)(server_t *server, data_player_t *player);
    
    
    typedef struct teams {
        char *name_teams;
        int nb_players;
        int id_chief;
        int chief_pos_x;
        int chief_pos_y;
    } teams_t;

    typedef struct network {
        int server_fd;
        int fd_gui;
        fd_set write_fd;
        fd_set read_fd;
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

    typedef enum ressource {
        FOOD = 0,
        LINEMATE = 1,
        DERAUMERE = 2,
        SIBUR = 3,
        MENDIANE = 4,
        PHIRAS = 5,
        THYSTAME = 6,
    } ressource_t;

    typedef enum direction {
        UP = 1,
        DOWN = 3,
        RIGHT = 2,
        LEFT = 4,
        NONE = -1,
    } dir_t;

    typedef struct orientation {
        dir_t dir;
        int up_left;
        int up_center;
        int up_right;
        int down_left;
        int down_center;
        int down_right;
        int center_left;
        int center_right;
    }orientation_t;

    typedef struct command {
        char *cmd_name;
        cmd_t cmd;
        int time_cycle;
    }command_t;

    typedef struct buffer {
        char *buffer;
        size_t capacity;
        size_t using_size;
    } buffer_t;

    typedef struct player_msg {
        buffer_t **msg_read;
        buffer_t **msg_write;
    } msg_t;
    
    typedef struct map_case {
        data_player_t **player_list;
        inventory_t *case_inventory;
    } map_case_t;

    typedef struct data_player_s {
        int id;
        int level;
        int pos_x;
        int pos_y;
        int fd;
        map_case_t *case_on_map;
        msg_t *msg_to_player;        
        teams_t *my_team;
        command_t *cmd;
        dir_t direction;
        inventory_t *inventory;
        int forward;
        bool deconnect;
        bool died;
        int life_time;
        int cmd_time;
        buffer_t *cmd_index;
    } data_player_t;

    typedef struct egg_player {
        map_case_t *case_on_map;
        teams_t *my_teams;
    }egg_player_t;

    typedef struct ms_gui {
        buffer_t **msg_read;
        buffer_t **msg_write;
    } ms_gui_t;

    typedef struct server {
        int port;
        int freq;
        int nb_players;
        int height;
        int width;
        int player_id;
        network_t *network;
        teams_t **teams_players;
        map_case_t **map;
        bool run;
        data_player_t **player_list;
        egg_player_t **egg_players;
        bool gui_authentifed;
        ms_gui_t *gui_msg;
        int map_time;
        clock_t start_time;
        clock_t end_time;
    } server_t;

    typedef struct {
        int x;
        int y;
    } coordinate;

    typedef struct Core_game {
        bool run_game;
    } core_game;
    
char **my_str_to_word_array(char const *str, char *delim);
int error_message(char *msg);
int manag_teams_name(int i, char **argv, server_t * server);
void usage(void);
int check_good_value_server(server_t *server);

int handle_args(int argc, char **argv, server_t *server);
int string_position(char **tab, char *str);
int server_init(server_t *server);
void init_case(inventory_t *inv);
int init_map_game(server_t *server);

int count_player_list(data_player_t **player_list);
void free_player(data_player_t *player);
void free_map(map_case_t **map, int x, int y);
void free_server2(server_t *server);

void free_server(server_t *server);
int fd_select(server_t *server);
int add_player_list(data_player_t *player, server_t *server);
int add_new_client(server_t *server);
int manag_back_fd(server_t *server);

int reload_map(server_t *server);
void print_tile_content(server_t *server, int height, int widht);
int count_array_gab(char **tab);
int run(server_t *server);
int init_msg_client(data_player_t *player);
int init_msg_client_bis(buffer_t **read, buffer_t **write);

int add_msg_reader(buffer_t **read, buffer_t *buffer);
int count_msg_tmp(buffer_t **read);
int read_message(data_player_t *player);
int read_message_gui(int fd_gui, server_t *server);

void handle_signal(int signal);
int welcome_client(data_player_t *player);

void delete_msg(char *buffer, buffer_t **read);
int new_player(data_player_t *player, server_t *server);

char *get_content_tile(server_t *server, int height, int widht);
int get_msg_send(char *msg, buffer_t **msg_send);
void get_msg_write_gui(char *msg, buffer_t ***msg_write);
void get_msg_read_gui(buffer_t *msg, buffer_t ***msg_read);

void send_msg(data_player_t *player);
void send_msg_gui(server_t *serv);
void new_player_msg(data_player_t *player, server_t *server);
int player_team_add(server_t *server, data_player_t *player, char *name);
void add_team_server_bis(server_t *server, int i, data_player_t *player,
teams_t *new_teams);

char *handle_great_msg_gui(char *msg);
int handle_command(server_t *serv);
void init_msg_gui(server_t *server);
inventory_t *get_inventory(int height, int width);

void add_player_in_case(map_case_t *cases, data_player_t *player);
void remove_player_in_case(map_case_t *cases, data_player_t *player);
void free_2d(char **tab);
void free_msg_client(msg_t *msg_to_player);

void execute_gui_cmd(server_t *serv);
int delete_players(data_player_t *player, server_t  *server);
int take_item_n_inventory(int nb, inventory_t *inventory, char *item);

int set_item_n_inventory(int nb, inventory_t *inventory, char *item);
void look_up_bis(data_player_t *player, server_t *server, int y, int x);
void look_down_bis(data_player_t *player, server_t *server, int y, int x);
void look_left_bis(data_player_t *player, server_t *server, int y, int x);
void look_right_bis(data_player_t *player, server_t *server, int y, int x);
void msg_gui_droping(server_t *server, data_player_t *player, int i);
void msg_gui_collect(server_t *server, data_player_t *player, int i);

int  check_level_player(data_player_t **player_list, int level);
void msg_start_incantation_lv_one(server_t *server, data_player_t *player,
data_player_t *player_two);
void msg_end_state_incantation(server_t *server, data_player_t *player,
char *status);
int *check_n_level_player(data_player_t **player_list, int level,
int nb_players);
int count_player_available(int *player_list, int nb_players);

void msg_start_incantation_lv_n(server_t *server, data_player_t *player,
data_player_t **players, int players_need);
void take_and_drop_lv_three(int *list, data_player_t *player, \
data_player_t **list_player, inventory_t *inventory_case);
void drop_thystame(int x, server_t *serv, data_player_t *player,
inventory_t *inventory);
void take_thystame(int x, server_t *serv, data_player_t *player,
inventory_t *inventory);
void inventory_case_bis(char *msg, inventory_t *inventory);
void get_param_incantation(data_player_t *player, server_t *server, char *cmd);
map_case_t *check_case_look(server_t *server, int y, int x);
int check_ressource(char *res);

char *remove_first_character(char* str);
int count_player_in_case(map_case_t *case_map);
bool check_inventory_case(inventory_t *cases);
char *name_of_ressource(ressource_t ressource);
char *get_tile_contents(map_case_t *cases, int players);
int number_case_look(int pos);
void shuffle(coordinate *array, int size);
void place_resources(server_t *server, inventory_t *inventory,
coordinate *coordinates, int size);
void place_resource1(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates);
void place_resource2(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates);
void place_resource3(int random, inventory_t *inventory, map_case_t *tile,
coordinate *coordinates);
void remove_from_list(data_player_t *player, server_t *server);

void manag_player_cmd(server_t *serv);
void manage_gui_command(server_t *serv);
void manag_life_players(server_t *server);
void second_manag_cmd_gui(server_t *serv, int i, char *cmd);

void manage_player_deconnection(server_t *serv);
int handle_cmd_bis(server_t *server, data_player_t *player);
void exec_player_cmd(data_player_t *player, server_t *server);
char *message_to_player(char **tab);
void free_msg_gui(ms_gui_t *gui_msg);
buffer_t *reference_cmd(char *buffer, buffer_t **read);
void delete_msg_cmd(buffer_t *buffer, buffer_t **read);
void free_eggs(server_t *server);
//void initialize_time(server_t *serv);
//void reset_timer(server_t *serv);
void action_on_time(server_t *serv);
void time_player_cmd(data_player_t *player);

// IA-CLIENTS COMMANDS
void forwad_cmd(server_t *server, data_player_t *player);
void forwad_bis_cmd(data_player_t *player, server_t *server);
void right_cmd(server_t *server, data_player_t *player);
void left_cmd(server_t *server, data_player_t *player);
void look_cmd(server_t *server, data_player_t *player);
void inventory_cmd(server_t *server, data_player_t *player);
void brodcast_cmd(server_t *server, data_player_t *player);
void connect_nbr_cmd(server_t *server, data_player_t *players);
void fork_cmd(server_t *server, data_player_t *player);
void eject_cmd(server_t *server, data_player_t *player);
void take_cmd(server_t *server, data_player_t *player);
void set_cmd(server_t *server, data_player_t *player);
void incantation_cmd(server_t *server, data_player_t *player);

// GUI-COMMANDS
void map_size(server_t *server, char *msg);
void content_tile(server_t *server, char *msg);
void send_all_content_tile_map(server_t *server, char *msg);
void name_of_teams(server_t *server, char *msg);
void send_time_unit(server_t *server, char *msg);
void send_update_unit(server_t *server, char *msg);
void player_position(server_t *server, int id_n);
void player_level(server_t *server, int id_n);
void player_inventory(server_t *server, int id_n);
#endif /* !SERVER_H_ */