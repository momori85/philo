/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:14:17 by amblanch          #+#    #+#             */
/*   Updated: 2025/05/08 15:01:12 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	ft_dead(t_create_philo *thread)
{
	pthread_mutex_lock(&thread->vars->mutex_status);
	thread->vars->status = 0;
	pthread_mutex_unlock(&thread->vars->mutex_status);
}

int	ft_verif_dead(t_create_philo *thread, int *count)
{
	long	time;

	while (1)
	{
		time = ft_get_time();
		if (ft_verif_status(thread) == 0)
			return (0);
		if (time - thread->time >= thread->vars->time_dead)
		{
			ft_dead(thread);
			ft_print_routine("died", thread, *count);
			pthread_mutex_unlock(&thread->fork);
			return (0);
		}
	}
	return (1);
}

int	ft_verif_nb_eat(t_create_philo *thread, int count)
{
	pthread_mutex_lock(&thread->vars->mutex_status);
	if (count >= thread->vars->nb_eat && thread->vars->nb_eat != -1)
	{
		pthread_mutex_unlock(&thread->vars->mutex_status);
		return (0);
	}
	pthread_mutex_unlock(&thread->vars->mutex_status);
	return (1);
}
