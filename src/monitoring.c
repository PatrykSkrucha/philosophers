/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:46 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 18:45:11 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	stop_dinner(t_main *main, t_philo *philo)
{
	long	i;
	long	diff;

	diff = get_time() - philo->main_struct->time_start;
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = DEAD;
	pthread_mutex_unlock(&philo->status_mutex);
	pthread_mutex_lock(&philo->main_struct->print);
	printf("%ld %lu died\n", diff, philo->id);
	i = 0;
	while (i < main->num_of_philos)
	{
		pthread_mutex_lock(&main->philos[i]->status_mutex);
		main->philos[i]->status = DEAD;
		pthread_mutex_unlock(&main->philos[i]->status_mutex);
		i++;
	}
	pthread_mutex_unlock(&philo->main_struct->print);
}

static int	life_check(t_main *main, int i)
{
	long	diff;

	pthread_mutex_lock(&main->philos[i]->time_mutex);
	diff = get_time() - main->philos[i]->last_eat;
	pthread_mutex_unlock(&main->philos[i]->time_mutex);
	if (diff >= main->time_to_die
		&& get_status(main->philos[i]) != FULLY_ATE)
	{
		stop_dinner(main, main->philos[i]);
		return (1);
	}
	return (0);
}

void	*monitoring(void *ptr)
{
	t_main	*main;
	int		i;
	int		meal_counter;

	meal_counter = 0;
	main = ptr;
	while (1)
	{
		i = 0;
		while (i < main->num_of_philos)
		{
			if (get_status(main->philos[i]) == FULLY_ATE)
			{
				meal_counter++;
				if (meal_counter == main->number_of_meals)
					return (NULL);
			}
			if (life_check(main, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
