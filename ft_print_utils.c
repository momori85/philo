/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:50:28 by amblanch          #+#    #+#             */
/*   Updated: 2025/05/08 16:08:48 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_tilte(void)
{
	printf("╭────────────┬────────────────┬───────────");
	printf("───────────┬────────────╮\n");
	printf("│    \033[1mTime\033[0m    │ \033[1mPhilosopher ");
	printf("ID\033[0m │             \033[1mAction\033[0m   ");
	printf("│ \033[1mMcDo eaten\033[0m │\n");
	printf("├────────────┼────────────────");
	printf("┼──────────────────────┼────────────┤\n");
}

void	ft_print_last(void)
{
	printf("╰─────────────────────────────────────");
	printf("────────────────────────────╯\n");
	printf("[SPONSORED] https://www.mcdonalds.fr/\n");
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
