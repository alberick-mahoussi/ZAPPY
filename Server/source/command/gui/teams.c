/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** teams
*/

#include "../../../include/server.h"

void name_of_teams(server_t *server, char *msg)
{
    char name[4096];
    name[0] = '\0';
    if (count_array_gab(my_str_to_word_array(msg, " ")) != 1)
        return;
    for (int i = 0; server->teams_players[i] != NULL; i++) {
        char temp[256];
        sprintf(temp, "tna %s\n", server->teams_players[i]->name_teams);
        strcat(name, temp);
    }
    get_msg_write_gui(strdup(name), &server->gui_msg->msg_write);
}
