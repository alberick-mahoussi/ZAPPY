##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## call_ia
##

import socket
import communication
import commandes
import mouvements
import level_up

def call_help(socket, player):
    print("I send I need a help")
    commandes.broadcast(socket, "I Need a help !")
    message = communication.receive_message(socket)
    while message.find("I am with you !") == -1:
        print("in while call_help")
        if message.find("I comming !") != -1:
            print("in if call_help")
            commandes.broadcast(socket, "Come to me !")
            print("I send Come to me")
        message = communication.receive_message(socket)
    print("he is with me")


def go_help(socket, player):
    print("I send I comming")
    commandes.broadcast(socket, "I comming !")
    message = communication.receive_message(socket)
    while True:
        print("message go help = " + message)
        if message.find("Come to me !") != -1:
            print("in the if go_help")
            info_msg = communication.parse_message(message)
            if info_msg[0] != 0:
                print("I am on my way")
                mouvements.rechearch_player(socket, player, info_msg[0])
                print("I send I comming")
                commandes.broadcast(socket, "I comming !")
            else:
                print("i send 'I am with you !'")
                commandes.broadcast(socket, "I am with you !")
                message = communication.receive_message(socket)
                break
        message = communication.receive_message(socket)

