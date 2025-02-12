/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:00:31 by amaury            #+#    #+#             */
/*   Updated: 2025/02/11 13:42:54 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_create_philo	*ft_lstnew(int content)
{
	t_create_philo	*list;

	list = malloc(sizeof(t_create_philo) * 1);
	if (list == 0)
		return (0);
	list->next = NULL;
	list->content = content;
	return (list);
}

void	ft_lstadd_front(t_create_philo **lst, t_create_philo *new)
{
	if (lst == NULL)
		return ;
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstclear(t_create_philo **lst, int len)
{
	t_create_philo	*i;
	t_create_philo	*next;
	int				count;

	count = 0;
	if (lst == 0)
		return ;
	i = *lst;
	if (i == 0)
		*lst = NULL;
	else
	{
		while (count < len && i)
		{
			next = i->next;
			free(i);
			i = next;
			count++;
		}
		*lst = NULL;
	}
}