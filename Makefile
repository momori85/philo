CC = cc 

FLAG = -Wall -Werror -Wextra -g

SRC = philo.c ft_create_list.c ft_create_philo.c ft_philo_utils.c ft_all_routine.c ft_lib_utils.c ft_print_utils.c ft_routine_left_and_right.c

NAME = philo

OBJ = $(SRC:.c=.o)

all: $(NAME)
	$(CC) -o $(NAME) $(SRC) $(FLAG)

$(NAME): $(OBJ)
	$(CC) -c $(SRC) $(FLAG)
	$(CC) -o $(NAME) $^ $(FLAG)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus