/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:16 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 18:50:49 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ptr;
	if (philo->id % 2 != 0)
	{
		usleep((philo->time_to_die / 4) * 1000);
	}
	while (get_status(philo) == ALIVE)
	{
		eat(philo);
		philo_sleep(philo);
		print_message(philo, THINK);
		ft_sleep(philo, philo->time_to_die / 4);
		i++;
	}
	return (NULL);
}

void	join_and_free(t_main *main, int i)
{
	while (i >= 0)
	{
		if (pthread_join(main->philos[i]->thread, NULL) != 0)
			print_error("Error occured during joining thread\n");
		i--;
	}
	destroy_mutex_status(main, main->num_of_philos, main->num_of_philos);
	pthread_mutex_destroy(&main->print);
	destroy_mutex_fork(main, main->num_of_philos);
	free_philos(main->num_of_philos, main);
}

int	start_simulation(t_main *main)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < main->num_of_philos)
	{
		update_meal_time(main->philos[i]);
		if (pthread_create(&main->philos[i]->thread, NULL,
				&routine, main->philos[i]) != 0)
		{
			print_error(("Failed to create thread\n"));
			join_and_free(main, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring, main) != 0)
	{
		print_error(("Failed to create thread\n"));
		join_and_free(main, main->num_of_philos);
		return (1);
	}
	if (pthread_join(monitor, NULL) != 0)
		print_error("Error occured during joining thread\n");
	return (0);
}

void	solo_dinner(t_main *main)
{
	print_message(main->philos[0], FORK);
	ft_sleep(main->philos[0], main->time_to_die);
	printf("%ld 1 died\n", main->time_to_die);
	free_philos(0, main);
}
