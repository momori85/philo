/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:14:17 by amblanch          #+#    #+#             */
/*   Updated: 2025/02/18 14:34:37 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif_died(t_create_philo *thread)
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

void	ft_print_routine(char *str, t_create_philo *thread, int count)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	printf("│\033[33m  %6ld ms \033[m│", (ft_get_time() - thread->time_init));
	printf("\033[36m n°%-12d \033[m│", thread->content);
	printf("\033[35m   %-16s   \033[m│\033[2m %5d McDo \033[m│\n", str, count);
	printf("├────────────┼────────────────┼");
	printf("──────────────────────┼────────────┤\n");
	pthread_mutex_unlock(&print_mutex);
}
