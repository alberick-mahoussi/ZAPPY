/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** map
*/

#include "../../../include/server.h"

void map_size(server_t *server, char *msg)
{
    if (count_array_gab(my_str_to_word_array(msg, " ")) != 1)
        return;
    char message[50];
    sprintf(message, "msz %d %d\n", server->width, server->height);
    get_msg_write_gui(strdup(message), &server->gui_msg->msg_write);
}

void content_tile(server_t *server, char *msg)
{
    int widht = 0;
    int height = 0;
    char **tab = my_str_to_word_array(msg, " ");
    if (tab == NULL || tab[1] == NULL || tab[2] == NULL) {
        free_2d(tab);
        return;
    }
    if (atoi(tab[1]) >= server->width && atoi(tab[2]) >= server->height) {
        get_msg_write_gui(strdup("ko\n"), &server->gui_msg->msg_write);
        free_2d(tab);
    }
    widht = atoi(tab[1]);
    height = atoi(tab[2]);
    print_tile_content(server, height, widht);
    free_2d(tab);
}

void send_all_content_tile_map(server_t *server, char *msg)
{
    char *tab = malloc(sizeof(char ) * (server->height * server->width * 50));
    tab[0] = '\0';
    if (count_array_gab(my_str_to_word_array(msg, " ")) != 1)
        return;
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            strcat(tab, get_content_tile(server, i, j));
        }
    }
    get_msg_write_gui(tab, &server->gui_msg->msg_write);
    free(tab);
}

void send_time_unit(server_t *server, char *msg)
{
    if (count_array_gab(my_str_to_word_array(msg, " ")) != 1)
        return;
    char message[50];
    sprintf(message, "sgt %d\n", server->freq);
    get_msg_write_gui(strdup(message), &server->gui_msg->msg_write);
}

void send_update_unit(server_t *server, char *msg)
{
    char *freq = NULL;
    if (count_array_gab(my_str_to_word_array(msg, " ")) != 2)
        return;
    freq = my_str_to_word_array(msg, " ")[1];
    if (is_number(freq) == 1) {
        server->freq = atoi(freq);
        char message[50];
        sprintf(message, "sst %d\n", server->freq);
        get_msg_write_gui(strdup(message), &server->gui_msg->msg_write);
    }
}
