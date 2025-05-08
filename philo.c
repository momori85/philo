/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:59:49 by amaury            #+#    #+#             */
/*   Updated: 2025/05/08 16:32:36 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_philo(t_philo *vars)
{
	t_create_philo	*thread;
	int				count;
	int				i;

	thread = ft_create_loop_list(vars, 0);
	i = -1;
	ft_print_tilte();
	while (++i < vars->nb_philo)
	{
		thread->time = ft_get_time();
		thread->time_init = ft_get_time();
		pthread_mutex_init(&thread->vars->mutex_status, NULL);
		pthread_mutex_init(&thread->vars->mutex_count, NULL);
		pthread_create(&thread->thread, NULL, ft_create_routine, thread);
		thread = thread->next;
	}
	count = 1;
	while (count <= vars->nb_philo)
	{
		pthread_join(thread->thread, NULL);
		thread = thread->next;
		count++;
	}
	ft_print_last();
	ft_lstclear(&thread, vars->nb_philo);
}

int	ft_error(int status, char *msg_error, char *str)
{
	if (status == -1 || ft_atoi_verif(str) == 0)
	{
		write(1, msg_error, ft_strlen(msg_error));
		return (0);
	}
	return (1);
}

int	ft_verif_args(t_philo *philo, char **argv, int argc)
{
	philo->nb_philo = ft_verif_arg_to_int(argv[1]);
	if (ft_error(philo->nb_philo, "error, nb philo not good !\n", argv[1]) == 0)
		return (0);
	philo->time_dead = ft_verif_arg_to_int(argv[2]);
	if (ft_error(philo->time_dead, "error, time dead not good !\n", \
		argv[2]) == 0)
		return (0);
	philo->time_eat = ft_verif_arg_to_int(argv[3]);
	if (ft_error(philo->time_eat, "error, time eat not good !\n", argv[3]) == 0)
		return (0);
	philo->time_sleep = ft_verif_arg_to_int(argv[4]);
	if (ft_error(philo->time_sleep, "error, time sleep not good !\n", \
		argv[4]) == 0)
		return (0);
	if (argc == 6)
	{
		philo->nb_eat = ft_verif_arg_to_int(argv[5]);
		if (ft_error(philo->nb_eat, "error, nb eat not good !\n", argv[5]) == 0)
			return (0);
	}
	else
		philo->nb_eat = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * 1);
	if (philo == 0)
	{
		free(philo);
		return (0);
	}
	if (argc != 5 && argc != 6)
	{
		write(1, "error, argument not good !\n", 27);
		free(philo);
		return (0);
	}
	if (ft_verif_args(philo, argv, argc) == 0)
		return (0);
	ft_create_philo(philo);
	free(philo);
	return (1);
}
