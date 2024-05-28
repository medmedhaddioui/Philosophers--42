NAME = philo_bonus

SRC = main.c simulation_philos.c init_bonus.c utils_bonus.c routine_bonus.c

OBJECT = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
