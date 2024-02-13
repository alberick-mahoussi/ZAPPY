/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** brodcast_tool
*/

#include "../../../include/server.h"

char *message_to_player(char **tab)
{
    char *message = NULL;
    int i = -1;
    int j = 1;
    int n = 0;

    for (; tab[j] != NULL; j++) {
        n = n + strlen(tab[j]) + 1;
    }

    message = malloc(sizeof(char) * n + 1);

    for (int j = 1; tab[j] != NULL; j++) {
        strcpy(message, tab[j]);
        strcat(message, " ");
    }
    return message;
}
