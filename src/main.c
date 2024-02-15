/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:38 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:08:41 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc < 2)
	{
		print_error("Too few arguments\n");
		return (1);
	}
	main = arrange_main(++argv);
	if (!main)
		return (1);
	if (main->num_of_philos == 1)
	{
		solo_dinner(main);
		return (0);
	}
	else
	{
		if (start_simulation(main))
			return (1);
	}
	join_and_free(main, --main->num_of_philos);
	return (0);
}
