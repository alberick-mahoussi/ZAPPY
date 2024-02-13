##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## commandes
##

import socket
import communication

def look_around(socket, player):
    communication.send_message(socket, "Look\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def look_inventory(socket, player):
    communication.send_message(socket, "Inventory\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def broadcast(socket, message):
    communication.send_message(socket, "Broadcast " + message + "\n")
    msg_receive = communication.receive_message(socket)
    return msg_receive

def team_unused_slots(socket):
    communication.send_message(socket, "Connect_nbr\n")
    return communication.receive_message(socket)

def fork_a_player(socket):
    communication.send_message(socket, "Fork\n")
    if (communication.receive_message(socket) == "ok\n"):
        return True
    return False

def eject_player(socket):
    communication.send_message(socket, "Eject\n")
    if (communication.receive_message(socket) == "ok\n"):
        return True
    return False

def death_of_a_player(socket):
    if (communication.receive_message(socket) == "dead\n"):
        return True
    return False

def take_object_and_listen(socket, object : str, player):
    communication.send_message(socket, "Take " + str(object) + "\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def drop_object(socket, player, object : str):
    communication.send_message(socket, "Set " + object + "\n")
    msg_receive = communication.receive_broadcast(socket, player)
    return msg_receive

def start_incantation(socket, player):
    communication.send_message(socket, "Incantation\n")
    msg_receive = communication.receive_broadcast(socket, player)
    print("send Incantation response = " + msg_receive)
    if (msg_receive == "Elevation underway\n"):
        print("ok i start incantation")
        msg_receive = communication.receive_broadcast(socket, player)
        return True
    return False
