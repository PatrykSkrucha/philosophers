/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:55 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 15:37:29 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_input(char **argv)
{
	if (ft_atoui32(argv[0]) <= 0)
	{
		print_error("Number of philos must be greater than 0\n");
		return (1);
	}
	if (ft_atoui32(argv[1]) < 0 || ft_atoui32(argv[2]) < 0
		|| ft_atoui32(argv[3]) < 0)
	{
		print_error("Incorrect input\n");
		return (1);
	}
	if (argv[4] && ft_atoui32(argv[4]) <= 0)
	{
		print_error("Number of meals must be positive number\n");
		return (1);
	}
	return (0);
}

static int	no_limit_meals(char **argv, t_main **main)
{
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	if (ft_atoui32(argv[0]) > 200)
	{
		print_error("Pass number of philos below 200");
		return (1);
	}
	if (check_input(argv))
		return (1);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->limited_dinner = false;
	return (0);
}

static int	limited_meals(char **argv, t_main **main)
{
	if (ft_atoui32(argv[0]) > 200)
	{
		print_error("Pass number of philos below 200");
		return (1);
	}
	if (check_input(argv))
		return (1);
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->number_of_meals = ft_atoui32(argv[4]);
	(*main)->limited_dinner = true;
	return (0);
}

int	get_input(t_main **main, char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 4)
	{
		if (no_limit_meals(argv, main))
			return (1);
	}
	else if (i == 5)
	{
		if (limited_meals(argv, main))
			return (1);
	}
	else
	{
		print_error("Incorrect input\n");
		return (1);
	}
	return (0);
}
