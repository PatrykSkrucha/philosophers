/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:55 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 15:36:19 by pskrucha         ###   ########.fr       */
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
	if (ft_atoui32(argv[1]) < 0 || ft_atoui32(argv[2]) < 0 ||
		ft_atoui32(argv[3]) < 0)
	{
		print_error("Incorrect input\n");
		return (1);
	}
	if (argv[4] && ft_atoui32(argv[4]) < 0)
	{
		print_error("Number of meals must be positive number\n");
		return (1);
	}
	return (0);
}

static void	no_limit_meals(char **argv, t_main **main)
{
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	if (ft_atoui32(argv[0]) > 200)
	{
		print_error("Pass number of philos below 200");
		exit_free(main);
	}
	if (check_input(argv))
		exit_free(main);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->limited_dinner = false;
}

static void	limited_meals(char **argv, t_main **main)
{
	if (ft_atoui32(argv[0]) > 200)
	{
		print_error("Pass number of philos below 200\n");
		exit_free(main);
	}
	if (check_input(argv))
		exit_free(main);
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->number_of_meals = ft_atoui32(argv[4]);
	(*main)->limited_dinner = true;
}

static void	split_args(char *argv, t_main **main)
{
	char	**temp_args;
	int		i;

	i = 0;
	temp_args = check_malloc(ft_split(argv, ' '));
	while (temp_args[i])
		i++;
	if (i == 4)
		no_limit_meals(temp_args, main);
	else if (i == 5)
		limited_meals(temp_args, main);
	else
		error_exit("Incorrect input\n");
	double_free(temp_args);
}

void	get_input(t_main **main, char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		split_args(*argv, main);
	else if (i == 4)
		no_limit_meals(argv, main);
	else if (i == 5)
		limited_meals(argv, main);
	else
	{
		print_error("Incorrect input\n");
		exit_free(main);
	}
	if (pthread_mutex_init(&(*main)->print, NULL))
	{
		print_error("Incorrect input\n");
		exit_free(main);
	}
}
