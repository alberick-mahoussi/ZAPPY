/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** eject_cmd
*/

#include "../../../include/server.h"

void forwad_eject(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1) {
        get_msg_send("ko\n", player->msg_to_player->msg_write);
        return;
    }
    int i = player->pos_x;
    int j = player->pos_y;
    forwad_bis_cmd(player, server);
    player->pos_x = player->pos_x >= server->width ? 0 : player->pos_x;
    player->pos_y = player->pos_y >= server->height ? 0 : player->pos_y;
    player->case_on_map = &server->map[player->pos_y][player->pos_x];
    remove_player_in_case(&server->map[j][i], player);
    add_player_in_case(&server->map[player->pos_y][player->pos_x], player);
}

void eject_player_on_case(server_t *server, data_player_t *player,
data_player_t *eject_player, dir_t direction)
{
    dir_t of = direction == UP ? DOWN : direction == DOWN ? UP :
    direction == LEFT ? RIGHT : direction == RIGHT ? LEFT : 0;
    char msg[50];
    char guid[50];
    player->direction = eject_player->direction;
    forwad_eject(server, player);
    sprintf(msg, "eject %d\n", of);
    sprintf(guid, "pex %d\n", player->id);
    get_msg_send(strdup(msg), player->msg_to_player->msg_write);
    if (server->network->fd_gui != -1 && server->gui_authentifed == true)
        get_msg_write_gui(strdup(guid), &server->gui_msg->msg_write);
}

void eject_cmd(server_t *server, data_player_t *player)
{
    if (count_array_gab(my_str_to_word_array(player->cmd->cmd_name, " "))
    != 1 || count_player_in_case(player->case_on_map) == 0) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return;
    }
    if (count_player_in_case(player->case_on_map) < 2) {
        get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
        return;
    }
    int i = 0;
    map_case_t *case_player = player->case_on_map;
    for (i = 0; case_player->player_list[i] != NULL; i++) {
        if (case_player->player_list[i]->id != player->id)
            eject_player_on_case(server, case_player->player_list[i],
            player, player->direction);
    }
    get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
}
