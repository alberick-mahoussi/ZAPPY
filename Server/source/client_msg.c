/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** client_msg
*/

#include "../include/server.h"

char *getlines(data_player_t *player)
{
    char *buf = malloc(sizeof(char) * 100);
    int read_value = 1;

    read_value = read(player->fd, buf, 100);
    if (read_value == -1) {
        player->deconnect = true;
        perror("read message");
        free(buf);
        return NULL;
    }
    buf[read_value] = '\0';
    for (int i = 0; i != strlen(buf); i++)
        if (buf[i] == '\r' || buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    return (buf);
}

int init_msg_client(data_player_t *player)
{
    player->msg_to_player = malloc(sizeof(msg_t));
    if (!player->msg_to_player)
        return (-1);

    player->msg_to_player->msg_read = calloc(11, sizeof(buffer_t*));
    player->msg_to_player->msg_write = calloc(11, sizeof(buffer_t*));

    if (!player->msg_to_player->msg_read ||
    !player->msg_to_player->msg_write) {
        perror("malloc failded on player buffer\n");
        return (-1);
    }
    return (0);
}

int read_message(data_player_t *player)
{
    buffer_t *buffer = calloc(1, sizeof(buffer_t));
    buffer->buffer = getlines(player);
    if (buffer->buffer == NULL) {
        free(buffer);
        return (-1);
    } if (count_msg_tmp(player->msg_to_player->msg_read) < 10) {
        printf("%s\n", buffer->buffer);
        add_msg_reader(player->msg_to_player->msg_read, buffer);
    } else {
        free(buffer->buffer);
        free(buffer);
        return (-1);
    }
    printf("%d\n", count_msg_tmp(player->msg_to_player->msg_read));
    return (0);
}

int get_msg_send(char *msg, buffer_t **msg_send)
{
    int i = 0;

    buffer_t *new_msg = malloc(sizeof(buffer_t));
    new_msg->buffer = msg;
    new_msg->using_size = strlen(msg) + 1;
    for (i = 0; msg_send[i] != NULL; i++);
    msg_send[i] = new_msg;
    msg_send[i + 1] = NULL;
}

void send_msg(data_player_t *player)
{
    int i = 0;
    for (i = 0; player->msg_to_player->msg_write[i] != NULL; i++) {
        if (write(player->fd, player->msg_to_player->msg_write[i]->buffer,
        strlen(player->msg_to_player->msg_write[i]->buffer)) == -1)
            player->deconnect = true;
        delete_msg(player->msg_to_player->msg_write[i]->buffer,
        player->msg_to_player->msg_write);
    }
}
