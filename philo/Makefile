NAME = philo

SRC = philo.c philo_utils.c philo2.c

OBJECT = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re