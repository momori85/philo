CC = cc 

FLAG = -Wall -Werror -Wextra -g

SRC = philo.c ft_create_list.c

NAME = philo

all:
	$(CC) -o $(NAME) $(SRC) $(FLAG)