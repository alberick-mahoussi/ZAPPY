/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
** File description:
** manag_gui
*/

#include "../include/server.h"

char *getlines_gui(int fd_gui)
{
    char *buf = malloc(sizeof(char) * 100);
    int read_value = 1;

    read_value = read(fd_gui, buf, 100);
    if (read_value == -1) {
        fd_gui = -1;
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

int read_message_gui(int fd_gui, server_t *server)
{
    buffer_t *buffer = calloc(1, sizeof(buffer_t));
    buffer->buffer = getlines_gui(fd_gui);
    if (buffer->buffer == NULL) {
        free(buffer);
        return (-1);
    }
    printf("%s\n", buffer->buffer);
    get_msg_read_gui(buffer, &server->gui_msg->msg_read);
    return 0;
}

int check_gui_demands(char *msg)
{
    char *cmd_gui[] = {
        "msz", "bct", "mct",
        "tna", "ppo", "plv",
        "pin", "sgt", "sst", NULL
    };
    char **tab = my_str_to_word_array(msg, " ");
    if (tab == NULL)
        return -1;
    int i = 0;
    int j = -1;
    for (int i = 0; cmd_gui[i] != NULL; i++) {
        if (strcmp(cmd_gui[i], tab[0]) == 0) {
            j = i;
            break;
        }
    }
    printf("%d\n", j);
    free_2d(tab);
    return (j);
}

void execute_gui_cmd_bis(server_t *serv, int i, char *cmd)
{
    switch (i) {
        case 3:
            name_of_teams(serv, cmd);
            break;
        case 4:
            count_array_gab(my_str_to_word_array(cmd, " ")) == 2 ?
            player_position(serv, atoi(remove_first_character
            (my_str_to_word_array(cmd, " ")[0]))) : 0;
            break;
        case 5:
            count_array_gab(my_str_to_word_array(cmd, " ")) == 2 ?
            player_level(serv, atoi(remove_first_character
            (my_str_to_word_array(cmd, " ")[0]))) : 0;
            break;
        default:
            second_manag_cmd_gui(serv, i, cmd);
    }
}

void execute_gui_cmd(server_t *serv)
{
    if (serv->gui_msg->msg_read == NULL || serv->gui_msg->msg_read[0] == NULL)
        return;
    char *msg = serv->gui_msg->msg_read[0]->buffer;
    int i = check_gui_demands(msg);
    switch (i) {
        case 0:
            map_size(serv, msg);
            break;
        case 1:
            content_tile(serv, msg);
            break;
        case 2:
            send_all_content_tile_map(serv, msg);
            break;
        default:
            execute_gui_cmd_bis(serv, i, msg);
    }
    delete_msg(serv->gui_msg->msg_read[0]->buffer, serv->gui_msg->msg_read);
}
