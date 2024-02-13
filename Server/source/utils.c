/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** utils
*/

#include "../include/server.h"

void delete_msg(char *buffer, buffer_t **read)
{
    int i = 0;
    int found_index = -1;
    buffer_t *msg = NULL;
    for (i = 0; read[i] != NULL; i++) {
        if (strcmp(read[i]->buffer, buffer) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index != -1) {
        msg = read[i];
        for (int j = found_index; read[j] != NULL; j++) {
            read[j] = (read[j + 1] != NULL) ? read[j + 1] : NULL;
        }
        free(msg->buffer);
        free(msg);
    }
}

void new_player_msg(data_player_t *player, server_t *server)
{
    int i = server->nb_players - player->my_team->nb_players;
    char msg[50];
    sprintf(msg, "%d\n%d %d\n", i, server->width, server->height);
    write(player->fd, msg, strlen(msg));
}

char* handle_great_msg_gui(char *msg)
{
    int i;
    for (i = 0; msg[i] != '\n' && msg[i] != '\0'; i++);
    char *buf = malloc(sizeof(char) * (i + 1));
    strncpy(buf, msg, i);
    buf[i] = '\0';
    return buf;
}

void init_msg_gui(server_t *server)
{
    server->gui_msg = malloc(sizeof(ms_gui_t));
    if (server->gui_msg == NULL)
        perror("malloc dont work in msg_gui\n");
    server->gui_msg->msg_read = calloc(11, sizeof(buffer_t *));
    if (server->gui_msg->msg_read == NULL)
        perror("malloc dont work in msg_gui read\n");

    server->gui_msg->msg_write = calloc(11, sizeof(buffer_t *));
    if (server->gui_msg->msg_write == NULL)
        perror("malloc tab msg gui write don't wrok\n");
}
