/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:00:31 by amaury            #+#    #+#             */
/*   Updated: 2025/02/12 09:08:10 by amblanch         ###   ########.fr       */
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
	list->prev = NULL;
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
		new->next->prev = new;
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