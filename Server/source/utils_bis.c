/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** utils_bis
*/

#include "../include/server.h"

char *remove_first_character(char* str)
{
    if (str[0] != '#')
        return str;
    int len = strlen(str);
    if (len > 0) {
        strcpy(str, str + 1);
    }
    return str;
}

int is_number(const char* str)
{
    if (str == NULL)
        return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void second_manag_cmd_gui(server_t *serv, int i, char *cmd)
{
    char *str = "suc\n";
    switch (i) {
        case 6:
            count_array_gab(my_str_to_word_array(cmd, " ")) == 2 ?
            player_inventory(serv, atoi(remove_first_character
            (my_str_to_word_array(cmd, " ")[0]))) : 0;
            break;
        case 7:
            send_time_unit(serv, cmd);
            break;
        case 8:
            send_update_unit(serv, cmd);
            break;
        default:
            get_msg_write_gui(strdup(str), &serv->gui_msg->msg_write);
    }
}

buffer_t *reference_cmd(char *buffer, buffer_t **read)
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
    if (found_index != -1)
        return read[found_index];
    return NULL;
}

void delete_msg_cmd(buffer_t *buffer, buffer_t **read)
{
    int i = 0;
    int found_index = -1;
    for (i = 0; read[i] != NULL; i++) {
        if (strcmp(read[i]->buffer, buffer->buffer) == 0) {
            found_index = i;
            break;
        }
    }
    for (int j = found_index; read[j] != NULL; j++) {
            read[j] = (read[j + 1] != NULL) ? read[j + 1] : NULL;
        }
    free(buffer->buffer);
    free(buffer);
}
