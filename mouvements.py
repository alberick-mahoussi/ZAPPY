##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## mouvements
##

import socket
import communication
import commandes
import algo

def move_Forward(socket, player):
    communication.send_message(socket, "Forward\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def turn_Right(socket, player):
    communication.send_message(socket, "Right\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def turn_Left(socket, player):
    communication.send_message(socket, "Left\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def move_to_one(socket, player):
    move_Forward(socket, player)

def move_to_two(socket, player):
    move_Forward(socket, player)
    turn_Left(socket, player)
    move_Forward(socket, player)

def move_to_three(socket, player):
    turn_Left(socket, player)
    move_Forward(socket, player)

def move_to_four(socket, player):
    turn_Left(socket, player)
    move_Forward(socket, player)
    turn_Left(socket, player)
    move_Forward(socket, player)

def move_to_five(socket, player):
    turn_Left(socket, player)
    turn_Left(socket, player)
    move_Forward(socket, player)

def move_to_six(socket, player):
    turn_Right(socket, player)
    move_Forward(socket, player)
    turn_Right(socket, player)
    move_Forward(socket, player)

def move_to_seven(socket, player):
    turn_Right(socket, player)
    move_Forward(socket, player)

def move_to_eight(socket, player):
    move_Forward(socket, player)
    turn_Right(socket, player)
    move_Forward(socket, player)

def rechearch_player(socket, player, pos : int):
    if pos == 1:
        move_to_one(socket, player)
        print("move to one")
    elif pos == 2:
        move_to_two(socket, player)
        print("move to two")
    elif pos == 3:
        move_to_three(socket, player)
        print("move to three")
    elif pos == 4:
        move_to_four(socket, player)
        print("move to four")
    elif pos == 5:
        move_to_five(socket, player)
        print("move to five")
    elif pos == 6:
        move_to_six(socket, player)
        print("move to six")
    elif pos == 7:
        move_to_seven(socket, player)
        print("move to seven")
    elif pos == 8:
        move_to_eight(socket, player)
        print("move to eight")
