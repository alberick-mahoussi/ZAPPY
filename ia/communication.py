##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## communication
##

import socket
import select
import communication
import re
import broadcast_check
import commandes
import sys

class Dead(Exception):
    """Base class for other exceptions"""
    pass

message_receive_pattern = r"message (\d), (.*)$"

def create_socket(HOST : str, PORT : int):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    return s

def send_message(socket, message : str):
    socket.send(message.encode('utf-8'))

def receive_message(socket):
    message = socket.recv(4024).decode('utf-8')
    if (message == "dead"):
        socket.close()
        raise Dead("I'm dead")
    return message

def receive_broadcast(socket, player):
    msg = receive_message(socket)
    print("msg receive by broad = ", msg)
    while (msg.find("message") != -1):
        broadcast_check.check_broad(socket, msg, player)
        msg = receive_message(socket)
        print("msg return by broad = ", msg)
    return msg

def parse_message(message):
    print("parse receive = ", message)
    match = re.match(message_receive_pattern, message)
    if match:
        k = int(match.group(1))
        text = match.group(2)
        return k, text
    else:
        print("Don't match")
        return None
