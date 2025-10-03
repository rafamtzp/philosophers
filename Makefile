NAME = philo

CFLAGS = -Wall -Wextra -Werror -g
CC = cc

SRC = helpers.c philo_actions.c init.c main.c exit.c parsing.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: $(OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re