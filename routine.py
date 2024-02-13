##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## routine
##

import mouvements
import algo
import commandes
import broadcast_check
import communication
import socket

def move_routine_boss(socket, player_object):
    commands = [
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.turn_Left,
        mouvements.move_Forward,
        mouvements.turn_Left,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.turn_Right,
        mouvements.move_Forward,
        mouvements.turn_Right
    ]

    for x in range(3):
        for command in commands:
            tmp = command(socket, player_object)
            if command == mouvements.move_Forward:
                command(socket, player_object)
                algo.take_everything(socket, player_object)

def move_routine_ia(socket, player_object):
    commands = [
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.turn_Left,
        mouvements.move_Forward,
        mouvements.turn_Left,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.move_Forward,
        mouvements.turn_Right,
        mouvements.move_Forward,
        mouvements.turn_Right
    ]

    for x in range(3):
        for command in commands:
            tmp = command(socket, player_object)
            if command == mouvements.move_Forward:
                command(socket, player_object)
                algo.take_everything(socket, player_object)
