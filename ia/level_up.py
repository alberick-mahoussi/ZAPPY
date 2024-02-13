##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## level_up
##

import socket
import incant
import data
import communication
import commandes
import inventor
import call_ia
import algo

def check_lvl_up(socket, player, level : int):
    inventory = inventor.stock_inventory(socket, player)
    if (int(inventory[0][1]) < 4):
        print("Not enough food")
        return False
    for i in range(1, len(data.requirement)):
        if (int(inventory[i][1]) < data.requirement[level][i]):
            return False
    return True

def lvl_up(socket, player_object):
    if (player_object.level != 1):
        call_ia.call_help(socket, player_object)
        algo.take_everything(socket, player_object, True)
        incant.drop_lvl_up(socket, player_object)
    if (player_object.level == 1):
        incant.drop_lvl_up(socket, player_object)
    if (commandes.start_incantation(socket, player_object) == True):
        player_object.level += 1
        commandes.broadcast(socket, "LEVEL_UP")
        print("LEVEL UP !", str(player_object.level))
