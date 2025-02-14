/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:33:29 by amblanch          #+#    #+#             */
/*   Updated: 2025/02/12 14:20:50 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create_routine(void *tmp)
{
	t_philo  *thread = (t_philo *)tmp;
	struct timeval time_now;
	int status;
	
	status = 0;
	while(1)
	{
		if (thread->vars->status == 1)
		{
			pthread_mutex_lock(&thread->vars->fork);
			thread->vars->status = 0;
			printf("philo %d eat\n", thread->vars->content);
			while (1)
			{
				gettimeofday(&time_now, NULL);
				printf("time = %d\n", thread->time_eat);
				if (time_now.tv_usec - thread->vars->time.tv_usec >= thread->time_eat)
				{
					gettimeofday(&thread->vars->time, NULL);
					break;
				}
			}
			thread->vars->status = 1;
			pthread_mutex_unlock(&thread->vars->fork);
		}
		else if (thread->vars->prev->status == 1)
		{
			pthread_mutex_lock(&thread->vars->prev->fork);
			thread->vars->prev->status = 0;
			printf("philo %d eat\n", thread->vars->content);
			while (1)
			{
				gettimeofday(&time_now, NULL);
				if (time_now.tv_usec - thread->vars->time.tv_usec >= thread->time_eat)
				{
					gettimeofday(&thread->vars->time, NULL);
					break;
				}
			}
			thread->vars->prev->status = 1;
			pthread_mutex_unlock(&thread->vars->prev->fork);
		}
		return (0);
	}
}

t_create_philo	*ft_create_loop_list(t_philo *thread)
{
	t_create_philo *tmp;
	int				count;

	count = 1;
	thread->vars = ft_lstnew(1);
	gettimeofday(&thread->vars->time, NULL);
	pthread_mutex_init(&thread->vars->fork, NULL);
	thread->vars->status = 1;
	pthread_create(&thread->vars->thread, NULL, ft_create_routine, thread);
	tmp  = thread->vars;
	printf("count philo = %d\n", thread->nb_philo);
	while (count < thread->nb_philo)
	{
		count++;
		ft_lstadd_front(&thread->vars, ft_lstnew(count));
		gettimeofday(&thread->vars->time, NULL);
		thread->vars->status = 1;
		pthread_mutex_init(&thread->vars->fork, NULL);
		pthread_create(&thread->vars->thread, NULL, ft_create_routine, thread);
		printf("count philo = %d\n", count);
	}
	tmp->next = thread->vars;
	tmp->next->prev = tmp;
	return (tmp);
}

void	ft_create_philo(t_philo *thread)
{
	int 			count;

	count = 0;
	thread->vars = ft_create_loop_list(thread);
	while (count < thread->nb_philo)
	{
		pthread_join(thread->vars->thread, NULL);
		thread->vars = thread->vars->next;
		count++;
	}
	count = 0;
	while (count < thread->nb_philo)
	{
		printf("philo = %d\n", thread->vars->content);
		thread->vars = thread->vars->next;
		count++;
	}
	ft_lstclear(&thread->vars, thread->nb_philo);
}
