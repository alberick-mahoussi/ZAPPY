##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-alberick.mahoussi
## File description:
## Makefile
##

SRC = 		$(shell echo source/command/gui/*.c) \
      		$(shell echo source/command/players/*.c) \
      		$(shell echo source/*.c)


OBJ 	=		$(SRC:.c=.o)

NAME	=		zappy_server

all:	$(NAME)

DEBUG	=	-g3

$(NAME): 	$(OBJ)
		gcc -o $(NAME) $(SRC) $(DEBUG)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re