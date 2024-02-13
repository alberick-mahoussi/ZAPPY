/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** utils_map
*/

#include "../include/server.h"

int count_player_list(data_player_t **player_list)
{
    if (player_list[0] == NULL)
        return 0;
    int i = 0;
    for (i = 0; player_list[i] != NULL; i++);
    return i;
}

void free_2d(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

int count_array_gab(char **tab)
{
    int i = 0;
    for (i = 0; tab[i] != NULL; i++);
    return i;
}
