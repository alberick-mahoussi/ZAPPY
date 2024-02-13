/*
** EPITECH PROJECT, 2023
** server_zappy
** File description:
** tool_look_bis
*/

#include "../../../include/server.h"

char *get_all_ressource(ressource_t ressource, int nb);

bool check_inventory_case(inventory_t *cases)
{
    if (cases->deraumere > 0 || cases->food > 0 || cases->linemate > 0 ||
    cases->mendiane > 0 || cases->phiras > 0 || cases->sibur > 0 ||
    cases->thystame > 0)
        return true;
    return false;
}

char *name_of_ressource(ressource_t ressource)
{
    switch (ressource) {
        case FOOD:
            return strdup ("food");
        case LINEMATE:
            return strdup ("linemate");
        case DERAUMERE:
            return strdup ("deraumere");
        case SIBUR:
            return strdup ("sibur");
        case MENDIANE:
            return strdup ("mendiane");
        case PHIRAS:
            return strdup ("phiras");
        case THYSTAME:
            return strdup ("thystame");
    }
    return NULL;
}

int number_case_look(int pos)
{
    int i = 0;
    if (pos == 0)
        return 3;
    if (pos == 1)
        i = 5;
    else
        i = 7;
    return i;
}

void inventory_case_bis(char *msg, inventory_t *inventory)
{
    if (inventory->linemate > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(LINEMATE, inventory->linemate));
    } if (inventory->deraumere > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(DERAUMERE, inventory->deraumere));
    } if (inventory->sibur > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(SIBUR, inventory->sibur));
    } if (inventory->mendiane > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(MENDIANE, inventory->mendiane));
    } if (inventory->phiras > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(PHIRAS, inventory->phiras));
    } if (inventory->thystame > 0) {
        msg[0] != '\0' ? strcat(msg, " ") : 0;
        strcat(msg, get_all_ressource(THYSTAME, inventory->thystame));
    }
}
