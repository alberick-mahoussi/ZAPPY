##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## locate_mouv
##

import commandes
import socket

def stock_look_around(socket, player_object):
    tab = commandes.look_around(socket, player_object)
    tab = tab.replace("\n", "")
    tab = tab.replace("[ ", "")
    tab = tab.replace(" ]", "")
    tab = tab.replace(",,", ", X,")
    tab = tab.split(", ")
    for i in range(len(tab)):
        tab[i] = tab[i].split(" ")
    return tab

def vision_around(socket, object):
    vision = stock_look_around(socket)
    for i in range(len(vision)):
        for j in range(len(vision[i])):
            if (vision[i][j] == object):
                return i
    return -1
