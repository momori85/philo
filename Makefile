CC = cc 

FLAG = -Wall -Werror -Wextra -g

SRC = philo.c ft_create_list.c ft_create_philo.c ft_philo_utils.c ft_all_routine.c ft_lib_utils.c ft_print_utils.c ft_routine_left_and_right.c

NAME = philo

all:
	$(CC) -o $(NAME) $(SRC) $(FLAG)