/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:57:35 by amaury            #+#    #+#             */
/*   Updated: 2025/02/12 14:15:15 by amblanch         ###   ########.fr       */
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


typedef struct s_create_philo
{
	struct s_create_philo	*next;
	struct s_create_philo	*prev;
	pthread_mutex_t			fork;
	struct timeval			time;
	pthread_t				thread;
	int						content;
	int 					status;
}				t_create_philo;

typedef struct s_philo
{
	int				nb_philo;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	t_create_philo *vars;
}				t_philo;

t_create_philo	*ft_lstnew(int content);
void			ft_lstadd_front(t_create_philo **lst, t_create_philo *new);
void			ft_lstclear(t_create_philo **lst, int len);
void			ft_create_philo(t_philo *philo);

#endif