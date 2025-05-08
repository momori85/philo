/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:33:29 by amblanch          #+#    #+#             */
/*   Updated: 2025/05/08 16:10:06 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_routine_even(t_create_philo *thread, int *count)
{
	if (pthread_mutex_lock(&thread->fork) == 0)
	{
		if (ft_verif_status_dead(thread) == 0)
		{
			pthread_mutex_unlock(&thread->fork);
			return (0);
		}
		ft_print_routine("has taken a fork", thread, *count);
		if (thread->vars->nb_philo == 1)
		{
			thread->time = ft_get_time();
			ft_verif_dead(thread, count);
			return (0);
		}
		if (pthread_mutex_lock(&thread->prev->fork) == 0)
		{
			if (ft_fork_right(thread, count) == 0)
				return (0);
		}
		else
		{
			pthread_mutex_unlock(&thread->fork);
		}
	}
	return (1);
}

int	ft_routine_odd(t_create_philo *thread, int *count)
{
	if (pthread_mutex_lock(&thread->prev->fork) == 0)
	{
		if (ft_verif_status_dead(thread) == 0)
		{
			pthread_mutex_unlock(&thread->prev->fork);
			return (0);
		}
		ft_print_routine("has taken a fork", thread, *count);
		if (thread->vars->nb_philo == 1)
		{
			thread->time = ft_get_time();
			ft_verif_dead(thread, count);
			return (0);
		}
		if (pthread_mutex_lock(&thread->fork) == 0)
		{
			if (ft_fork_left(thread, count) == 0)
				return (0);
		}
		else
		{
			pthread_mutex_unlock(&thread->prev->fork);
		}
	}
	return (1);
}

int	ft_routine_condition(t_create_philo *thread, int *count)
{
	if (ft_verif_nb_eat(thread, *count) == 0)
		return (0);
	if (thread->content % 2 == 0)
		if (ft_routine_even(thread, count) == 0)
			return (0);
	if (thread->content % 2 == 1)
		if (ft_routine_odd(thread, count) == 0)
			return (0);
	if (ft_sleep_routine(thread, *count) == 0)
	{
		pthread_mutex_lock(&thread->vars->mutex_count);
		thread->vars->count += *count;
		pthread_mutex_unlock(&thread->vars->mutex_count);
		return (0);
	}
	return (1);
}

void	*ft_create_routine(void *tmp)
{
	t_create_philo	*thread;
	int				running;
	int				count;

	count = 0;
	running = 1;
	thread = (t_create_philo *)tmp;
	while (running)
	{
		if (ft_routine_condition(thread, &count) == 0)
			return (0);
	}
	pthread_mutex_lock(&thread->vars->mutex_count);
	thread->vars->count += count;
	pthread_mutex_unlock(&thread->vars->mutex_count);
	return (NULL);
}

t_create_philo	*ft_create_loop_list(t_philo *vars, int count)
{
	t_create_philo	*thread;
	t_create_philo	*first;
	t_create_philo	*last;
	t_create_philo	*node;

	count = 1;
	thread = NULL;
	if (vars->nb_philo == 0)
		return (0);
	while (count <= vars->nb_philo)
	{
		node = ft_lstnew(count, vars);
		ft_lstadd_front(&thread, node);
		count++;
	}
	if (thread)
	{
		first = thread;
		last = thread;
		while (last->next != NULL)
			last = last->next;
		last->next = first;
		first->prev = last;
	}
	return (thread);
}
