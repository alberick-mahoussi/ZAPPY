##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## algo
##

import socket
import communication
import locate_mouv
import inventor
import mouvements
import commandes
import data
import incant
import routine
import level_up
import call_ia

def take_everything(socket, player_object, on_me = False):
    liste = locate_mouv.stock_look_around(socket, player_object)
    if (on_me == True):
        for i in liste[0]:
            if (i != "player" and i != "" and i != "X"):
                commandes.take_object_and_listen(socket, i, player_object)
    if (on_me == False and player_object.level == 1):
        for i in range(min(len(liste), 2)):
            if i == 1:
                mouvements.move_Forward(socket, player_object)
            if i == 2:
                mouvements.turn_Left(socket, player_object)
                mouvements.move_Forward(socket, player_object)
                mouvements.turn_Right(socket, player_object)
            for j in liste[i]:
                if (j != "player" and j != "" and j != "X"):
                    commandes.take_object_and_listen(socket, j, player_object)
    if (on_me == False and player_object.level >= 2 and player_object.level <= 4):
        for i in range(min(len(liste), 6)):
            if i == 1:
                mouvements.move_Forward(socket, player_object)
            if i == 2:
                mouvements.turn_Left(socket, player_object)
                mouvements.move_Forward(socket, player_object)
                mouvements.turn_Right(socket, player_object)
            if i == 3:
                mouvements.move_Forward(socket, player_object)
                mouvements.turn_Right(socket, player_object)
            if i == 4:
                mouvements.move_Forward(socket, player_object)
            if i == 5:
                mouvements.move_Forward(socket, player_object)
            if i == 6:
                mouvements.move_Forward(socket, player_object)
                mouvements.turn_Left(socket, player_object)
            for j in liste[i]:
                if (j != "player" and j != "" and j != "X"):
                    commandes.take_object_and_listen(socket, j, player_object)

def routine_boss(socket, player_object):
    while (player_object.level != 3):
        if (level_up.check_lvl_up(socket, player_object, player_object.level + 1) == True):
            level_up.lvl_up(socket, player_object)
        take_everything(socket, player_object)
        take_everything(socket, player_object)
        if (player_object.is_Boss == False):
            break

def routine_ia(socket, player_object):
    while (player_object.level != 3):
        if (level_up.check_lvl_up(socket, player_object, player_object.level + 1) == True):
            level_up.lvl_up(socket, player_object)
        take_everything(socket, player_object)
        take_everything(socket, player_object)
        print("Inventory after IA = " + commandes.look_inventory(socket, player_object))
