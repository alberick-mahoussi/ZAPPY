##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## incant
##

import commandes
import socket

def drop_lvl_up(socket, player):
    if (player.level == 1):
        commandes.drop_object(socket, player, "linemate")
    if (player.level == 2):
        commandes.drop_object(socket, player, "linemate")
        commandes.drop_object(socket, player, "deraumere")
        commandes.drop_object(socket, player, "sibur")
    if (player.level == 3):
        commandes.drop_object(socket, player, "linemate")
        commandes.drop_object(socket, player, "linemate")
        commandes.drop_object(socket, player, "sibur")
        commandes.drop_object(socket, player, "phiras")
        commandes.drop_object(socket, player, "phiras")
