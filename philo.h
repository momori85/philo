/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:57:35 by amaury            #+#    #+#             */
/*   Updated: 2025/05/08 16:24:59 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb_philo;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	pthread_mutex_t	mutex_count;
	int				count;
	int				status;
	pthread_mutex_t	mutex_status;
}				t_philo;

typedef struct s_create_philo
{
	struct s_create_philo	*next;
	struct s_create_philo	*prev;
	pthread_mutex_t			fork;
	time_t					time;
	time_t					time_init;
	pthread_t				thread;
	int						content;
	t_philo					*vars;
}				t_create_philo;

t_create_philo	*ft_lstnew(int content, t_philo *vars);
void			ft_lstadd_front(t_create_philo **lst, t_create_philo *new);
void			ft_lstclear(t_create_philo **lst, int len);
void			ft_create_philo(t_philo *philo);
int				ft_verif_died(t_create_philo *thread);
time_t			ft_get_time(void);
void			ft_dead(t_create_philo *thread);
void			ft_print_routine(char *str, t_create_philo *thread, int count);
int				ft_eat_routine(t_create_philo *thread, int count);
int				ft_sleep_routine(t_create_philo *thread, int count);

int				ft_isdigit(int number);
int				ft_atoi(const char *str);
int				ft_verif_arg_to_int(char *str);
int				ft_strlen(char *str);

void			ft_print_tilte(void);
void			ft_print_last(void);

void			*ft_create_routine(void *tmp);
int				ft_verif_status(t_create_philo *thread);
int				ft_verif_nb_eat(t_create_philo *thread, int count);
int				ft_fork_left(t_create_philo *thread, int *count);
int				ft_fork_right(t_create_philo *thread, int *count);
int				ft_count_eat(t_create_philo *thread, int *count);
t_create_philo	*ft_create_loop_list(t_philo *vars, int count);
int				ft_verif_dead(t_create_philo *thread, int *count);
int				ft_verif_status_dead(t_create_philo *thread);
int				ft_atoi_verif(const char *str);

#endif