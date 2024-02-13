/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** manag_cmd
*/

#include "../include/server.h"

const command_t ALL_COMMAND[] = {
    {"Forward", forwad_cmd, 7 },
    {"Right", right_cmd, 7},
    {"Left", left_cmd, 7},
    {"Look", look_cmd, 7},
    {"Inventory", inventory_cmd, 1},
    {"Broadcast", brodcast_cmd, 7},
    {"Connect_nbr", connect_nbr_cmd, 0},
    //{"Fork", fork_cmd, 42},
    {"Eject", eject_cmd, 7},
    {"Take", take_cmd, 7},
    {"Set", set_cmd, 7},
    {"Incantation", incantation_cmd, 300},
    {NULL, NULL, 0}
};

void msg_unkwon_cmd(data_player_t *ply, server_t *server, char *cmd)
{
    get_msg_send(strdup("ko\n"), ply->msg_to_player->msg_write);
    delete_msg(cmd, ply->msg_to_player->msg_read);
}

int get_param_cmd(data_player_t *player, int i, char *cmd)
{
    if (player->cmd == NULL) {
        player->cmd = malloc(sizeof(command_t));
        player->cmd->cmd_name = NULL;
    }
    player->cmd->cmd_name = strdup(cmd);
    player->cmd->cmd = ALL_COMMAND[i].cmd;
    player->cmd->time_cycle = ALL_COMMAND[i].time_cycle;
    return 0;
}

int choice_command(data_player_t *ply, server_t *server, char *cmd)
{
    int i = -1;
    char **tab = my_str_to_word_array(cmd, " ");
    if (tab == NULL)
        return (-1);
    for (int j = 0; ALL_COMMAND[j].cmd_name != NULL ; j++) {
        if (tab[0] == NULL)
            continue;
        if (strcasecmp(tab[0], ALL_COMMAND[j].cmd_name) == 0) {
            ply->cmd_index = reference_cmd(cmd, ply->msg_to_player->msg_read);
            get_param_cmd(ply, j, cmd);
            i = j;
            free_2d(tab);
            return (0);
        }
    }
    if (i == -1) {
        msg_unkwon_cmd(ply, server, cmd);
    }
    free_2d(tab);
    return (0);
}

int handle_cmd_bis(server_t *server, data_player_t *player)
{
    char *buff = player->msg_to_player->msg_read[0]->buffer;
    int i = 0;
    if (buff == NULL) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
        return (0);
    }
    if (player->my_team == NULL) {
        i = player->fd;
        player_team_add(server, player, buff);
        i != server->network->fd_gui ? delete_msg(buff, \
        player->msg_to_player->msg_read) : 0;
    } else {
        choice_command(player, server, buff);
    }
    return (0);
}

int handle_command(server_t *serv)
{
    manage_gui_command(serv);
    manag_player_cmd(serv);
    manage_player_deconnection(serv);
    return (0);
}
