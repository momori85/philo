/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:43 by amblanch          #+#    #+#             */
/*   Updated: 2025/05/08 16:07:39 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif_status_dead(t_create_philo *thread)
{
	pthread_mutex_lock(&thread->vars->mutex_status);
	if (thread->vars->status == 0)
	{
		pthread_mutex_unlock(&thread->vars->mutex_status);
		return (0);
	}
	pthread_mutex_unlock(&thread->vars->mutex_status);
	return (1);
}

int	ft_verif_status(t_create_philo *thread)
{
	pthread_mutex_lock(&thread->vars->mutex_status);
	if (thread->vars->status == 0)
	{
		pthread_mutex_unlock(&thread->vars->mutex_status);
		pthread_mutex_unlock(&thread->fork);
		pthread_mutex_unlock(&thread->prev->fork);
		return (0);
	}
	pthread_mutex_unlock(&thread->vars->mutex_status);
	return (1);
}

int	ft_eat_condition(time_t tmp, t_create_philo *thread, int count)
{
	if (tmp - thread->time >= thread->vars->time_dead)
	{
		ft_dead(thread);
		ft_print_routine("died", thread, count);
		pthread_mutex_unlock(&thread->fork);
		pthread_mutex_unlock(&thread->prev->fork);
		return (0);
	}
	return (1);
}

int	ft_eat_routine(t_create_philo *thread, int count)
{
	time_t	time_diff;
	time_t	tmp;

	if (ft_verif_status(thread) == 0)
		return (0);
	ft_print_routine("is thinking", thread, count);
	if (ft_verif_status(thread) == 0)
		return (0);
	ft_print_routine("is eating", thread, count);
	time_diff = ft_get_time();
	while (1)
	{
		tmp = ft_get_time();
		if (tmp - time_diff >= thread->vars->time_eat)
			break ;
		if (ft_eat_condition(tmp, thread, count) == 0)
			return (0);
		usleep(1);
		if (ft_verif_status(thread) == 0)
			return (0);
	}
	return (1);
}

int	ft_sleep_routine(t_create_philo *thread, int count)
{
	time_t	time_diff;
	time_t	tmp;

	if (ft_verif_status(thread) == 0)
		return (0);
	ft_print_routine("is sleeping", thread, count);
	time_diff = ft_get_time();
	if (ft_verif_status(thread) == 0)
		return (0);
	while (1)
	{
		tmp = ft_get_time();
		if (tmp - time_diff >= thread->vars->time_sleep)
			break ;
		if (tmp - thread->time >= thread->vars->time_dead)
		{
			ft_dead(thread);
			ft_print_routine("died", thread, count);
			return (0);
		}
		usleep(1);
		if (ft_verif_status(thread) == 0)
			return (0);
	}
	return (1);
}
