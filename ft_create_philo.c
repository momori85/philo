/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:33:29 by amblanch          #+#    #+#             */
/*   Updated: 2025/04/23 10:43:28 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void *ft_create_routine(void *tmp)
{
    t_create_philo *thread = (t_create_philo *)tmp;
    int running = 1;
	int count;
	long time;

	count = 0;
    while (running)
    {
        pthread_mutex_lock(&thread->vars->mutex_status);
		if (count >= thread->vars->nb_eat)
		{
			pthread_mutex_unlock(&thread->vars->mutex_status);
			return (NULL);
		}
        pthread_mutex_unlock(&thread->vars->mutex_status);
        if (thread->content % 2 == 0)
        {
            if (pthread_mutex_lock(&thread->fork) == 0)
            {
				if (ft_verif_died(thread) == 0)
				{
					pthread_mutex_unlock(&thread->fork);
					return (NULL);
				}
				ft_print_routine("has taken a fork", thread, count);
				if (thread->vars->nb_philo == 1)
				{
					while (1)
					{
						time = ft_get_time();
						if (time - thread->time >= thread->vars->time_dead)
						{
							ft_dead(thread);
							ft_print_routine("died", thread, count);
							pthread_mutex_unlock(&thread->fork);
							return (0);
						}
					}
				}
                if (pthread_mutex_lock(&thread->prev->fork) == 0)
                {
					if (ft_verif_died(thread) == 0)
					{
						pthread_mutex_unlock(&thread->prev->fork);
                    	pthread_mutex_unlock(&thread->fork);
						return (NULL);
					}
					ft_print_routine("has taken a fork", thread, count);
                    thread->time = ft_get_time();
					count++;
                    if (ft_eat_routine(thread, count) == 0)
					{
						pthread_mutex_lock(&thread->vars->mutex_count);
						thread->vars->count += count;
						pthread_mutex_unlock(&thread->vars->mutex_count);
                        return NULL;
					}
                    pthread_mutex_unlock(&thread->prev->fork);
                    pthread_mutex_unlock(&thread->fork);
					pthread_mutex_lock(&thread->vars->mutex_status);
					if (count >= thread->vars->nb_eat)
					{
						pthread_mutex_unlock(&thread->vars->mutex_status);
						pthread_mutex_lock(&thread->vars->mutex_count);
						thread->vars->count += count;
						pthread_mutex_unlock(&thread->vars->mutex_count);
						return (NULL);
					}
       				pthread_mutex_unlock(&thread->vars->mutex_status);
                }
                else
                {
                    pthread_mutex_unlock(&thread->fork);
                }
            }
        }
        else
        {
            if (pthread_mutex_lock(&thread->prev->fork) == 0)
            {
				if (ft_verif_died(thread) == 0)
				{
					pthread_mutex_unlock(&thread->prev->fork);
					return (NULL);
				}
				ft_print_routine("has taken a fork", thread, count);
				if (thread->vars->nb_philo == 1)
				{
					while (1)
					{
						time = ft_get_time();
						if (time - thread->time >= thread->vars->time_dead)
						{
							ft_dead(thread);
							ft_print_routine("died", thread, count);
							pthread_mutex_unlock(&thread->prev->fork);
							return (0);
						}
					}
				}
                if (pthread_mutex_lock(&thread->fork) == 0)
                {
					if (ft_verif_died(thread) == 0)
					{
						pthread_mutex_unlock(&thread->prev->fork);
                   		pthread_mutex_unlock(&thread->fork);
						return (NULL);
					}
					ft_print_routine("has taken a fork", thread, count);
                    thread->time = ft_get_time();
					count++;
                    if (ft_eat_routine(thread, count) == 0)
					{
						pthread_mutex_lock(&thread->vars->mutex_count);
						thread->vars->count += count;
						pthread_mutex_unlock(&thread->vars->mutex_count);
                        return NULL;
					}
                    pthread_mutex_unlock(&thread->prev->fork);
                    pthread_mutex_unlock(&thread->fork);
					pthread_mutex_lock(&thread->vars->mutex_status);
					if (count >= thread->vars->nb_eat)
					{
						pthread_mutex_unlock(&thread->vars->mutex_status);
						pthread_mutex_lock(&thread->vars->mutex_count);
						thread->vars->count += count;
						pthread_mutex_unlock(&thread->vars->mutex_count);
						return (NULL);
					}
       				pthread_mutex_unlock(&thread->vars->mutex_status);
                }
                else
                {
                    pthread_mutex_unlock(&thread->prev->fork);
                }
            }
        }
        if (ft_sleep_routine(running, thread, count) == 0)
		{
			pthread_mutex_lock(&thread->vars->mutex_count);
			thread->vars->count += count;
			pthread_mutex_unlock(&thread->vars->mutex_count);
            return NULL;
		}
    }
	pthread_mutex_lock(&thread->vars->mutex_count);
	thread->vars->count += count;
	pthread_mutex_unlock(&thread->vars->mutex_count);
    return NULL;
}




t_create_philo	*ft_create_loop_list(t_philo *vars)
{
	int				count;
	t_create_philo *thread;
	t_create_philo *node;

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
		t_create_philo *first = thread;
		t_create_philo *last = thread;
		while (last->next != NULL)
			last = last->next;
		last->next = first;
		first->prev = last;
	}
	t_create_philo *head = thread;
	return head;
}


void	ft_create_philo(t_philo *vars)
{
	t_create_philo *thread;
	int 			count;
	pthread_mutex_t mutex_count = PTHREAD_MUTEX_INITIALIZER;
	int				i;

	thread = ft_create_loop_list(vars);
	i = 0;
	printf("╭────────────┬────────────────┬──────────────────────┬────────────╮\n");
	printf("│    \033[1mTime\033[0m    │ \033[1mPhilosopher ID\033[0m │             \033[1mAction\033[0m   │ \033[1mMcDo eaten\033[0m │\n");
	printf("├────────────┼────────────────┼──────────────────────┼────────────┤\n");
	while (i < vars->nb_philo)
	{
		thread->time = ft_get_time();
		thread->time_init = ft_get_time();
		pthread_create(&thread->thread, NULL, ft_create_routine, thread);
		thread = thread->next;
		i++;
	}
	int totalMcdo = 0;
	for (count = 1; count <= vars->nb_philo; count++)
	{
		pthread_mutex_lock(&mutex_count);
		totalMcdo += thread->vars->count;
		pthread_mutex_unlock(&mutex_count);
		pthread_join(thread->thread, NULL);
		thread = thread->next;
	}
	float price = totalMcdo * 8.2;
	printf("├────────────┴────────────────┴──────────────────────┴────────────┤\n");
	printf("│ \033[1mQTY  ITEM                                      UNIT    TOTAL    \033[0m│\n");
	printf("│ x%4d Golden Roy.Delux                         8.20   %8.2f  │\n", totalMcdo, totalMcdo * 8.2);
	printf("│    x%4d Coke Max Best Of                                       │\n", totalMcdo);
	printf("│    x%4d Fries MaxiBestOf                                       │\n", totalMcdo);
	printf("│    x%4d Nugg4 ds Golden                       1.00   %8.2f  │\n", totalMcdo, totalMcdo * 1.0);
	printf("│      x%4d Barbecue                            0.65   %8.2f  │\n", totalMcdo*2, totalMcdo * 0.65 * 2);
	printf("│                                                                 │\n");
	printf("│                                            TOTAL HT : %8.2f€ │\n", (price + (totalMcdo * 0.65 * 2) + totalMcdo ));
	printf("│                                     \033[1mTOTAL TTC (10%%) : %8.2f€\033[0m │\n", (price + (totalMcdo * 0.65 * 2) + totalMcdo ) * 1.10);
	printf("╰─────────────────────────────────────────────────────────────────╯\n");
	printf("[SPONSORED] https://www.mcdonalds.fr/\n");
	ft_lstclear(&thread, vars->nb_philo);
}
