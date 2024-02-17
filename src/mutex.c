/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:55 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 14:25:23 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex_status(t_main *main, int i, int j)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&main->philos[i]->status_mutex);
		i--;
	}
	while (j >= 0)
	{
		pthread_mutex_destroy(&main->philos[j]->time_mutex);
		j--;
	}
}

int	time_status(t_main **main)
{
	int	i;

	i = 0;
	while (i < (*main)->num_of_philos)
	{
		if (pthread_mutex_init(&(*main)->philos[i]->status_mutex, NULL))
		{
			destroy_mutex_status(*main, i, -1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < (*main)->num_of_philos)
	{
		if (pthread_mutex_init(&(*main)->philos[i]->time_mutex, NULL))
		{
			destroy_mutex_status(*main, (*main)->num_of_philos, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_mutex(t_main **main)
{
	if (time_status(main))
		return (1);
	if (pthread_mutex_init(&(*main)->print, NULL))
	{
		destroy_mutex_status(*main, (*main)->num_of_philos,
			(*main)->num_of_philos);
		return (1);
	}
	if (hand_out_forks(main))
		return (1);
	return (0);
}
