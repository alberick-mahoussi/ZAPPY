##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## main
##

import argparse
import sys
import communication
import commandes
import data
import mouvements
import algo

class Error(Exception):
    """Base class for other exceptions"""
    pass

def error_handling(args: list):
    if (len(args) != 6):
        raise Error("Wrong number of arguments")

def get_args(args: list):
    parser = argparse.ArgumentParser(add_help=False, exit_on_error=True)
    parser.add_argument("-p", type=int)
    parser.add_argument("-n", type=str)
    parser.add_argument("-h", type=str)
    liste = parser.parse_args()
    return liste

def handle_boss(socket, player_object):
    msg_send = "I have a Boss ?"
    commandes.broadcast(socket, msg_send)
    commandes.take_object_and_listen(socket, "linemate", player_object)
    commandes.take_object_and_listen(socket, "food", player_object)
    if (player_object.is_Boss == True):
        print("I'm the boss")
        algo.routine_boss(socket, player_object)
    if (player_object.is_Boss == False):
        print("I'm not the boss")
        algo.routine_ia(socket, player_object)

if __name__ == "__main__":
    try:
        error_handling(sys.argv[1:])
        args = get_args(sys.argv[1:])
        socket = communication.create_socket(args.h, args.p)
        print(communication.receive_message(socket))
        communication.send_message(socket, args.n + "\n")
        player_object = data.player(1,args.n)
        print(communication.receive_message(socket))
        handle_boss(socket, player_object)
        print("level = " + str(player_object.level))
    except Error as e:
        print(e)
        socket.close()
        sys.exit(84)
    except KeyboardInterrupt:
        socket.close()
        sys.exit(84)