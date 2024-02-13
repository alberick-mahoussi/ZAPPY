/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** client_msg_bis
*/

#include "../include/server.h"

void init_msg_struct(buffer_t *buffer)
{
    buffer->buffer = malloc(sizeof(char) * 50);
    buffer->capacity = 0;
    buffer->capacity = 0;
}

int init_msg_client_bis(buffer_t **read, buffer_t **write)
{
    int i = 0;

    for (i = 0; i < 11; i++) {
        read[i] = malloc(sizeof(buffer_t));
        write[i] = malloc(sizeof(buffer_t));
        init_msg_struct(read[i]);
        init_msg_struct(write[i]);
    }
    read[i] = NULL;
    write[i] = NULL;
    return 0;
}

int count_msg_tmp(buffer_t **read)
{
    int count = 0;

    while (read[count] != NULL) count++;
    return count;
}

int add_msg_reader(buffer_t **read, buffer_t *buffer)
{
    int i = 0;
    for (i = 0; read[i] != NULL; i++);
    read[i] = buffer;
    return i;
}
