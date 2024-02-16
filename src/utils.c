/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:29 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:09:30 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
}

void	ft_sleep(t_philo *philo, long value)
{
	long	start_time;
	long	time_lap;

	start_time = get_time();
	time_lap = get_time() - start_time;
	while (time_lap < value)
	{
		if (get_status(philo) != ALIVE)
			return ;
		usleep(50);
		time_lap = get_time() - start_time;
	}
}
