/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_left_and_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:53:20 by amblanch          #+#    #+#             */
/*   Updated: 2025/05/08 14:56:25 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_count_eat(t_create_philo *thread, int *count)
{
	pthread_mutex_unlock(&thread->vars->mutex_status);
	pthread_mutex_lock(&thread->vars->mutex_count);
	thread->vars->count += *count;
	pthread_mutex_unlock(&thread->vars->mutex_count);
	return (0);
}

int	ft_fork_right(t_create_philo *thread, int *count)
{
	if (ft_verif_status(thread) == 0)
	{
		pthread_mutex_unlock(&thread->prev->fork);
		pthread_mutex_unlock(&thread->fork);
		return (0);
	}
	ft_print_routine("has taken a fork", thread, *count);
	thread->time = ft_get_time();
	(*count)++;
	if (ft_eat_routine(thread, *count) == 0)
	{
		pthread_mutex_lock(&thread->vars->mutex_count);
		thread->vars->count += *count;
		pthread_mutex_unlock(&thread->vars->mutex_count);
		return (0);
	}
	pthread_mutex_unlock(&thread->prev->fork);
	pthread_mutex_unlock(&thread->fork);
	pthread_mutex_lock(&thread->vars->mutex_status);
	if (*count >= thread->vars->nb_eat && thread->vars->nb_eat != -1)
		return (ft_count_eat(thread, count));
	pthread_mutex_unlock(&thread->vars->mutex_status);
	return (1);
}

int	ft_fork_left(t_create_philo *thread, int *count)
{
	if (ft_verif_status(thread) == 0)
	{
		pthread_mutex_unlock(&thread->prev->fork);
		pthread_mutex_unlock(&thread->fork);
		return (0);
	}
	ft_print_routine("has taken a fork", thread, *count);
	thread->time = ft_get_time();
	(*count)++;
	if (ft_eat_routine(thread, *count) == 0)
	{
		pthread_mutex_lock(&thread->vars->mutex_count);
		thread->vars->count += *count;
		pthread_mutex_unlock(&thread->vars->mutex_count);
		return (0);
	}
	pthread_mutex_unlock(&thread->prev->fork);
	pthread_mutex_unlock(&thread->fork);
	pthread_mutex_lock(&thread->vars->mutex_status);
	if (*count >= thread->vars->nb_eat)
		return (ft_count_eat(thread, count));
	pthread_mutex_unlock(&thread->vars->mutex_status);
	return (1);
}
