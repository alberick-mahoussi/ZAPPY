/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** brodcast_cmd
*/

#include "../../../include/server.h"

const orientation_t ORIENTATIONS[] = {
    { UP, 2, 1, 8, 4, 5, 6, 3, 7 },
    { RIGHT, 4, 3, 2, 6, 7, 8, 5, 1 },
    { DOWN, 6, 5, 4, 8, 1, 2, 7, 3 },
    { LEFT, 8, 7, 6, 2, 3, 4, 1, 5 }
};

int get_sound_vector(data_player_t *sender, data_player_t *recver,
server_t *server)
{
    int dx = abs(recver->pos_x - sender->pos_x);
    int dy = abs(recver->pos_y - sender->pos_y);

    if (dx > server->width / 2) {
        if (recver->pos_x < sender->pos_x)
            dx = server->width - (sender->pos_x - recver->pos_x);
        else
            dx = server->width - (recver->pos_x - sender->pos_x);
    }

    if (dy > server->height / 2) {
        if (recver->pos_y < sender->pos_y)
            dy = server->height - (sender->pos_y - recver->pos_y);
        else
            dy = server->height - (recver->pos_y - sender->pos_y);
    }
    return dx + dy;
}

int get_sound_orientation(server_t *server, data_player_t *sender,
data_player_t *recver)
{
    int i = recver->direction - 1;
    if (sender->pos_x == recver->pos_x && sender->pos_y == recver->pos_y)
        return 0;
    int shortest_distance = get_sound_vector(sender, recver, server);
    if (shortest_distance == ORIENTATIONS[i].up_left)
        return (ORIENTATIONS[i].up_left);
    if (shortest_distance == ORIENTATIONS[i].center_left)
        return (ORIENTATIONS[i].center_left);
    if (shortest_distance == ORIENTATIONS[i].down_left)
        return (ORIENTATIONS[i].down_left);
    if (shortest_distance == ORIENTATIONS[i].up_center)
        return (ORIENTATIONS[i].up_center);
    if (shortest_distance == ORIENTATIONS[i].down_center)
        return (ORIENTATIONS[i].down_center);
    if (shortest_distance == ORIENTATIONS[i].up_right)
        return (ORIENTATIONS[i].up_right);
    if (shortest_distance == ORIENTATIONS[i].center_right)
        return (ORIENTATIONS[i].center_right);
    if (shortest_distance == ORIENTATIONS[i].down_right)
        return (ORIENTATIONS[i].down_right);
}

void brodcast_cmd(server_t *server, data_player_t *player)
{
    char **tab = my_str_to_word_array(player->cmd->cmd_name, " ");
    char *msg = NULL;
    char all_msg[4096];
    char guid[4096];
    int  k = 0;
    if (tab == NULL || count_array_gab(tab) < 2) {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
    }
    get_msg_send(strdup("ok\n"), player->msg_to_player->msg_write);
    msg = message_to_player(tab);
    for (int i = 0; server->player_list[i] != NULL; i++) {
        k = get_sound_orientation(server, player, server->player_list[i]);
        sprintf(all_msg, "message %d, %s\n", i, msg);
        get_msg_send(strdup(all_msg), \
        server->player_list[i]->msg_to_player->msg_write);
    }
    sprintf(guid, "pbc %d %s\n", player->id, msg);
    if (server->network->fd_gui != -1 && server->gui_authentifed == true)
        get_msg_write_gui(strdup(guid), &server->gui_msg->msg_write);
    free(msg);
}
