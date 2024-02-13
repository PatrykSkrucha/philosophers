/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:36 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:51:11 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_main(t_main *main)
{
	__uint32_t	i;

	i = 0;
	printf("num of philos: %ld\n", main->num_of_philos);
	while (i < main->num_of_philos)
	{
		free(main->philos[i]);
		i++;
	}
	if (i > 0)
		free(main->philos);
	free(main);
}

long	ft_atoui32(char *str)
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
	printf("hereeee\n");
	free(*main);
	exit (1);
}

void	print_error(char *message)
{
	write(2, message, ft_strlen(message));
}