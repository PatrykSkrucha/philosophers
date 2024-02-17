/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:29 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 14:45:10 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	count_meals(t_philo *philo)
{
	if (!philo->limited_dinner)
		return ;
	philo->number_of_meals--;
	if (philo->number_of_meals == 0)
	{
		pthread_mutex_lock(&philo->status_mutex);
		philo->status = FULLY_ATE;
		pthread_mutex_unlock(&philo->status_mutex);
	}
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(&philo->r_fork);
		print_message(philo, FORK);
	}
}

void	eat(t_philo *philo)
{
	if (get_status(philo) != ALIVE)
		return ;
	grab_forks(philo);
	print_message(philo, EAT);
	update_meal_time(philo);
	count_meals(philo);
	ft_sleep(philo, philo->time_to_eat);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (get_status(philo) != ALIVE)
		return ;
	print_message(philo, SLEEP);
	ft_sleep(philo, philo->time_to_sleep);
}

void	solo_dinner(t_philo *philo)
{
	long	diff;

	print_message(philo, FORK);
	ft_sleep(philo, philo->time_to_die);
	diff = get_time() - philo->main_struct->time_start;
	printf("%ld 1 died\n", diff);
}
