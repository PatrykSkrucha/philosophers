/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:16 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:09:18 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ptr;
	update_meal_time(philo);
	if (philo->id % 2 != 0)
	{
		print_message(philo, THINK);
		usleep(100);
	}
	while (get_status(philo) == ALIVE)
	{
		eat(philo);
		philo_sleep(philo);
		print_message(philo, THINK);
		i++;
	}
	return (NULL);
}

void	start_simulation(t_main *main)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < main->num_of_philos)
	{
		if (pthread_create(&main->philos[i]->thread, NULL,
				&routine, main->philos[i]) != 0)
			error_exit("Failed to create thread\n");
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring, main) != 0)
		error_exit("Failed to create thread\n");
	if (pthread_join(monitor, NULL) != 0)
		error_exit("Failed to create thread\n");
}

void	stop_simulation(t_main *main)
{
	long	i;

	i = 0;
	while (i < main->num_of_philos)
	{
		if (pthread_join(main->philos[i]->thread, NULL))
			error_exit("Failure during joining threads\n");
		i++;
	}
	i = 0;
	while (i < main->num_of_philos)
	{
		pthread_mutex_destroy(&main->philos[i]->r_fork);
		i++;
	}
}
