##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## broadcast_check
##

import socket
import commandes
import call_ia

def check_broad(socket, message, player):
    print("message = " + message)
    if message.find("I have a Boss ?") != -1: # Si un joueur demande si il y a un boss
        commandes.broadcast(socket, "Im the boss")
        player.nbr_of_ia += 1
    if message.find("Im the boss") != -1: # Si un joueur dit qu'il est le boss
        player.is_Boss = False
    if message.find("I Need a help !") != -1 and player.level >= 2: # Si un joueur demande de l'aide
        call_ia.go_help(socket, player)
    if message.find("LEVEL_UP") != -1:
        player.level += 1
