##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## inventor
##

import commandes
import socket

def stock_inventory(socket, player_object):
    tab = commandes.look_inventory(socket, player_object)
    tab = tab.replace("\n", "")
    tab = tab.replace("[ ", "")
    tab = tab.replace(" ]", "")
    tab = tab.replace(",,", ", X,")
    tab = tab.split(", ")
    for i in range(len(tab)):
        tab[i] = tab[i].split(" ")
    return tab
