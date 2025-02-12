/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:57:35 by amaury            #+#    #+#             */
/*   Updated: 2025/02/11 14:00:35 by amaury           ###   ########.fr       */
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
	pthread_t  thread;
	struct s_create_philo	*next;
	int			content;
	struct timeval			time;
}				t_create_philo;

typedef struct s_philo
{
	int		nb_philo;
	int		time_dead;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
}				t_philo;

t_create_philo	*ft_lstnew(int content);
void	ft_lstadd_front(t_create_philo **lst, t_create_philo *new);
void	ft_lstclear(t_create_philo **lst, int len);

#endif