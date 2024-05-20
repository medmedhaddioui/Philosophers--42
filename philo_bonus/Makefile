NAME = philo_bonus

SRC = main.c philos.c init.c utils.c

OBJECT = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
