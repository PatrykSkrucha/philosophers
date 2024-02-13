/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:46 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:08:48 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	stop_dinner(t_main *main, t_philo *philo)
{
	long	i;

	pthread_mutex_lock(&philo->status_mutex);
	philo->status = DEAD;
	pthread_mutex_unlock(&philo->status_mutex);
	print_message(philo, DEATH);
	i = 0;
	while (i < main->num_of_philos)
	{
		pthread_mutex_lock(&main->philos[i]->status_mutex);
		main->philos[i]->status = DEAD;
		pthread_mutex_unlock(&main->philos[i]->status_mutex);
		i++;
	}
}

void	*monitoring(void *ptr)
{
	t_main	*main;
	long	diff;
	int		i;

	main = ptr;
	while (1)
	{
		i = 0;
		while (i < main->num_of_philos)
		{
			if (get_status(main->philos[i]) == FULLY_ATE)
				return (NULL);
			pthread_mutex_lock(&main->philos[i]->time_mutex);
			diff = get_time() - main->philos[i]->last_eat;
			pthread_mutex_unlock(&main->philos[i]->time_mutex);
			if (diff >= main->time_to_die
				&& get_status(main->philos[i]) != FULLY_ATE)
			{
				stop_dinner(main, main->philos[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
