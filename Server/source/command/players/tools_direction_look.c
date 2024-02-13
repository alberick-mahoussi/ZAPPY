/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tools_direction_look
*/

#include "../../../include/server.h"

void look_up_bis(data_player_t *player, server_t *server, int y, int x)
{
    map_case_t *case_map = NULL;
    char msg[10000];
    msg[0] = '\0';
    char *tmp = msg;
    strcat(tmp, "[");
    for (int i = 0; i < player->level; i++) {
        int num_columns = number_case_look(i);
        for (int j = 0; j < num_columns; j++) {
            case_map = check_case_look(server, y - i, x + j);
            int nb_players = count_player_in_case(case_map);
            char *case_content = get_tile_contents(case_map, nb_players);
            printf("%s\n", case_content);
            strcat(tmp, case_content);
            j < num_columns - 1 ? strcat(tmp, ", ") : 0;
            free(case_content);
        }
    }
    strcat(tmp, "]\n");
    get_msg_send(strdup(tmp), player->msg_to_player->msg_write);
}

void look_down_bis(data_player_t *player, server_t *server, int y, int x)
{
    map_case_t *case_map = NULL;
    char msg[10000];
    msg[0] = '\0';
    char *tmp = msg;
    strcat(tmp, "[");
    for (int i = 0; i < player->level; i++) {
        int num_columns = number_case_look(i);
        for (int j = 0; j < num_columns; j++) {
            case_map = check_case_look(server, y - i, x - j);
            int nb_players = count_player_in_case(case_map);
            char *case_content = get_tile_contents(case_map, nb_players);
            printf("%s\n", case_content);
            strcat(tmp, case_content);
            j < num_columns - 1 ? strcat(tmp, ", ") : 0;
            free(case_content);
        }
    }
    strcat(tmp, "]\n");
    get_msg_send(strdup(tmp), player->msg_to_player->msg_write);
}

void look_left_bis(data_player_t *player, server_t *server, int y, int x)
{
    map_case_t *case_map = NULL;
    char msg[10000];
    msg[0] = '\0';
    char *tmp = msg;
    strcat(tmp, "[");
    for (int i = 0; i < player->level; i++) {
        int num_columns = number_case_look(i);
        for (int j = 0; j < num_columns; j++) {
            case_map = check_case_look(server, y - j, x - i);
            int nb_players = count_player_in_case(case_map);
            char *case_content = get_tile_contents(case_map, nb_players);
            printf("%s\n", case_content);
            strcat(tmp, case_content);
            j < num_columns - 1 ? strcat(tmp, ", ") : 0;
            free(case_content);
        }
    }
    strcat(tmp, "]\n");
    get_msg_send(strdup(tmp), player->msg_to_player->msg_write);
}

void look_right_bis(data_player_t *player, server_t *server, int y, int x)
{
    map_case_t *case_map = NULL;
    char msg[10000];
    msg[0] = '\0';
    char *tmp = msg;
    strcat(tmp, "[");
    for (int i = 0; i < player->level; i++) {
        int num_columns = number_case_look(i);
        for (int j = 0; j < num_columns; j++) {
            case_map = check_case_look(server, y + j, x + i);
            int nb_players = count_player_in_case(case_map);
            char *case_content = get_tile_contents(case_map, nb_players);
            printf("%s\n", case_content);
            strcat(tmp, case_content);
            j < num_columns - 1 ? strcat(tmp, ", ") : 0;
            free(case_content);
        }
    }
    strcat(tmp, "]\n");
    get_msg_send(strdup(tmp), player->msg_to_player->msg_write);
}
