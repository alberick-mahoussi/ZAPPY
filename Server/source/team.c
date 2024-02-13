/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** team
*/

#include "../include/server.h"

void msg_gui_connection(data_player_t *player, server_t *server)
{
    char msg[50];
    if (server->network->fd_gui != -1) {
        sprintf(msg, "pnw #%d %d %d %d %d %s\n", player->id, player->pos_x,
        player->pos_y, player->direction, player->level,
        player->my_team->name_teams);
        if (server->network->fd_gui != -1 && server->gui_authentifed == true)
            get_msg_write_gui(strdup(msg), &server->gui_msg->msg_write);
    }
}

int player_new_team(data_player_t * player, teams_t *new_teams, char *name)
{
    if (new_teams->name_teams == NULL)
        new_teams->name_teams = strdup(name);
    new_teams->id_chief = player->id;
    new_teams->chief_pos_x = player->pos_x;
    new_teams->chief_pos_y = player->pos_y;
    return 0;
}

int add_player_team(server_t *server, teams_t *team, data_player_t *player)
{
    if (team->nb_players < server->nb_players) {
        new_player(player, server);
        (team->nb_players == 0) ? player_new_team(player, team, NULL) : 0;
        team->nb_players += 1;
        player->my_team = team;
        new_player_msg(player, server);
        msg_gui_connection(player, server);
    } else {
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
    }
    return 0;
}

int player_team_add(server_t *serv, data_player_t *player, char *nm)
{
    int i = -1;
    int j = 0;
    for (j = 0; serv->teams_players[j] != NULL; j++)
        if (strcmp(nm, serv->teams_players[j]->name_teams) == 0) {
            i = j;
            break;
        }
    if (i == -1 && strcmp("GRAPHIC", nm) == 0 && serv->network->fd_gui == -1) {
        serv->player_id -= 1;
        serv->gui_authentifed = true;
        serv->network->fd_gui = player->fd;
        init_msg_gui(serv);
        remove_from_list(player, serv);
        return 0;
    }
    if (i != -1)
        add_player_team(serv, serv->teams_players[i], player);
    else
        get_msg_send(strdup("ko\n"), player->msg_to_player->msg_write);
    return 0;
}
