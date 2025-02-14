/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:59:49 by amaury            #+#    #+#             */
/*   Updated: 2025/02/12 14:14:50 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_isdigit(int number)
{
    if (number > 47 && number < 58)
        return (1);
    return (0);
}

int     ft_atoi(const char *str)
{
        int     result;
        int     minus;

        minus = 1;
        result = 0;
        while ((*str >= 9 && *str <= 13) || *str == ' ')
                str++;
        if (*str == '+' || *str == '-')
        {
                if (*str == '-')
                        minus = -1;
                str++;
        }
        while (ft_isdigit(*str))
                result = (result * 10) + (*str++ - 48);
        return (result * minus);
}


// verifie si le str est composer que de nombre
int ft_verif_arg_to_int(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (ft_atoi(str));
}
int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}


int	ft_error(int status, char *msg_error)
{
	if (status == -1)
	{
		write(1, msg_error, ft_strlen(msg_error));
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_create_philo) * 1);
	if (philo == 0)
		return (0);
	philo->vars = malloc(sizeof(t_philo) * 1);
	if (philo->vars == 0)
		return (0);
	if (argc != 5 && argc != 6)
	{
		write(1, "error, argument not good !\n", 27);
		return (0);
	}
	philo->nb_philo = ft_verif_arg_to_int(argv[1]);
	if (ft_error(philo->nb_philo, "error, nb philo not good !\n") == 0)
		return (0);
	philo->time_dead = ft_verif_arg_to_int(argv[2]);
	if (ft_error(philo->time_dead, "error, time dead not good !\n") == 0)
		return (0);
	philo->time_eat = ft_verif_arg_to_int(argv[3]);
	if (ft_error(philo->time_eat, "error, time eat not good !\n") == 0)
		return (0);
	philo->time_sleep = ft_verif_arg_to_int(argv[4]);
	if (ft_error(philo->time_sleep, "error, time sleep not good !\n") == 0)
		return (0);
	if (argc == 6)
	{
		philo->nb_eat = ft_verif_arg_to_int(argv[5]);
		if (ft_error(philo->nb_eat, "error, nb eat not good !\n") == 0)
			return (0);
	}
	else
		philo->nb_eat = -1;
	printf("nb philo = %d | time dead = %d | time eat %d | time sleep %d | param = %d\n", philo->nb_philo, philo->time_dead, philo->time_eat, philo->time_sleep, philo->nb_eat);
	ft_create_philo(philo);
	return (1);
}