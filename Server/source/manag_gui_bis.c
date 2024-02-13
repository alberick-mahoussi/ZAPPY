/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** manag_gui_bis
*/

#include "../include/server.h"

void send_msg_gui(server_t *serv)
{
    int i = 0;
    for (i = 0; serv->gui_msg->msg_write[i] != NULL; i++) {
        if (write(serv->network->fd_gui, serv->gui_msg->msg_write[i]->buffer,
        strlen(serv->gui_msg->msg_write[i]->buffer)) == -1)
            serv->network->fd_gui = -1;
        delete_msg(serv->gui_msg->msg_write[i]->buffer,
        serv->gui_msg->msg_write);
    }
}

void get_msg_read_gui_bis(buffer_t *msg, buffer_t **read)
{
    int index = 0;
    while (read[index] != NULL) {
        index++;
    }
    read[index] = msg;
    read[index + 1] = NULL;
}

void get_msg_write_gui_bis(char *msg, buffer_t **write)
{
    int index = 0;
    buffer_t *buffer = calloc(1, sizeof(buffer_t));
    if (buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        return;
    }
    while (write[index] != NULL) {
        index++;
    }
    buffer->buffer = strdup(msg);
    write[index] = buffer;
    write[index + 1] = NULL;
}

void get_msg_read_gui(buffer_t *msg, buffer_t ***msg_read)
{
    int i = 0;
    int index = 0;
    buffer_t **new_msg_read = NULL;
    for (i = 0; (*msg_read)[i] != NULL; i++);
    if (i == 10) {
        new_msg_read = realloc(*msg_read,
        sizeof(buffer_t*) * (i + 2));
        if (new_msg_read == NULL) {
            fprintf(stderr, "Erreur de réallocation du tableau.\n");
            return;
        }
        *msg_read = new_msg_read;
    }
    get_msg_read_gui_bis(msg, *msg_read);
}

void get_msg_write_gui(char *msg, buffer_t ***msg_write)
{
    int i = 0;
    int index = 0;
    buffer_t **new_msg_write = NULL;
    for (i = 0; (*msg_write)[i] != NULL; i++);
    if (i == 10) {
        new_msg_write = realloc(*msg_write,
        sizeof(buffer_t*) * (i + 2));
        if (new_msg_write == NULL) {
            fprintf(stderr, "Erreur de réallocation du tableau.\n");
            return;
        }
        *msg_write = new_msg_write;
    }
    get_msg_write_gui_bis(msg, *msg_write);
}
