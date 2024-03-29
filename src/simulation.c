/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:16 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 19:12:51 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->main_struct->num_of_philos == 1)
	{
		solo_dinner(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		usleep((philo->time_to_die / 4) * 1000);
	}
	while (get_status(philo) == ALIVE)
	{
		eat(philo);
		philo_sleep(philo);
		print_message(philo, THINK);
		if (philo->main_struct->num_of_philos % 2)
			ft_sleep(philo, (philo->time_to_die / 4));
	}
	return (NULL);
}

void	join_and_free(t_main *main, int i)
{
	int	phil_num;

	i--;
	phil_num = i;
	while (i >= 0)
	{
		if (pthread_join(main->philos[i]->thread, NULL) != 0)
			print_error("Error occured during joining thread\n");
		i--;
	}
	destroy_mutex_status(main, phil_num, phil_num);
	pthread_mutex_destroy(&main->print);
	destroy_mutex_fork(main, phil_num);
	free_philos(phil_num, main);
}

void	join_and_free_philo_error(t_main *main, int i)
{
	int	j;

	j = i;
	pthread_mutex_lock(&main->print);
	while (i >= 0)
	{
		pthread_mutex_lock(&main->philos[i]->status_mutex);
		main->philos[i]->status = DEAD;
		pthread_mutex_unlock(&main->philos[i]->status_mutex);
		i--;
	}
	pthread_mutex_unlock(&main->print);
	while (j >= 0)
	{
		if (pthread_join(main->philos[j]->thread, NULL) != 0)
			print_error("Error occured during joining thread\n");
		j--;
	}
	main->num_of_philos--;
	destroy_mutex_status(main, main->num_of_philos, main->num_of_philos);
	pthread_mutex_destroy(&main->print);
	destroy_mutex_fork(main, main->num_of_philos);
	free_philos(main->num_of_philos, main);
}

void	join_and_free_monitoring_error(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&main->print);
	while (i < main->num_of_philos)
	{
		pthread_mutex_lock(&main->philos[i]->status_mutex);
		main->philos[i]->status = DEAD;
		pthread_mutex_unlock(&main->philos[i]->status_mutex);
		i++;
	}
	pthread_mutex_unlock(&main->print);
	i = 0;
	while (i < main->num_of_philos)
	{
		if (pthread_join(main->philos[i]->thread, NULL) != 0)
			print_error("Error occured during joining thread\n");
		i++;
	}
	main->num_of_philos--;
	destroy_mutex_status(main, main->num_of_philos, main->num_of_philos);
	pthread_mutex_destroy(&main->print);
	destroy_mutex_fork(main, main->num_of_philos);
	free_philos(main->num_of_philos, main);
}

int	start_simulation(t_main *main)
{
	int			i;

	i = 0;
	while (i < main->num_of_philos)
	{
		update_meal_time(main->philos[i]);
		if (pthread_create(&main->philos[i]->thread, NULL,
				&routine, main->philos[i]) != 0)
		{
			print_error(("Failed to create philo thread\n"));
			join_and_free_philo_error(main, --i);
			return (1);
		}
		i++;
	}
	if (main->num_of_philos > 1 && monitoring(main))
	{
		join_and_free(main, main->num_of_philos);
		return (1);
	}
	return (0);
}
