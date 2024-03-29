/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:36 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 15:52:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_main(t_main *main)
{
	long	i;

	i = 0;
	while (i < main->num_of_philos)
	{
		free(main->philos[i]);
		i++;
	}
	if (i > 0)
		free(main->philos);
	free(main);
}

long	ft_atol(char *str)
{
	long	number;

	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\n' || *str == '\f' || *str == '\r'
		|| *str == '+')
		str++;
	if (*str == '-')
		return (-1);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (number);
}

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	exit_free(t_main **main)
{
	free(*main);
	exit (1);
}

int	print_error(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}
