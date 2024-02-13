##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## data
##

class player:
    def __init__(self, level, team):
        self.level = level
        self.team = team
        self.is_Boss = True
        self.nbr_of_ia = 0

requirement = {
    2 : [1, 1, 0, 0, 0, 0, 0],
    3 : [2, 1, 1, 1, 0, 0, 0],
    4 : [2, 2, 0, 1, 0, 2, 0],
    5 : [4, 1, 1, 2, 0, 1, 0],
    6 : [4, 1, 2, 1, 3, 0, 0],
    7 : [6, 1, 2, 3, 0, 1, 0],
    8 : [6, 2, 2, 2, 2, 2, 1]
}