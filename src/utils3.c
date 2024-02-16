/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:42 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 17:36:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_main	*arrange_main(char **argv)
{
	t_main	*main;

	main = (malloc(sizeof(t_main)));
	if (!main && print_error("Malloc failure\n"))
		return (NULL);
	if (get_input(&main, argv))
	{
		free(main);
		return (NULL);
	}
	if (invite_philos(&main))
		return (NULL);
	if (set_mutex(&main) && print_error("Mutex failure\n"))
	{
		free_philos(main->num_of_philos, main);
		return (NULL);
	}
	main->time_start = get_time();
	return (main);
}

long	get_time(void)
{
	t_timeval		start_time;
	long			curr;

	gettimeofday(&start_time, NULL);
	curr = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (curr);
}

t_status	get_status(t_philo *philo)
{
	t_status	status;

	pthread_mutex_lock(&philo->status_mutex);
	status = philo->status;
	pthread_mutex_unlock(&philo->status_mutex);
	return (status);
}

void	print_message(t_philo *philo, t_activity activity)
{
	long		diff;
	const char	*type_str[] = {
	[EAT] = "is eating",
	[FORK] = "has taken a fork",
	[SLEEP] = "is sleeping",
	[THINK] = "is thinking",
	};

	diff = get_time() - philo->main_struct->time_start;
	pthread_mutex_lock(&philo->main_struct->print);
	if (get_status(philo) != ALIVE)
	{
		pthread_mutex_unlock(&philo->main_struct->print);
		return ;
	}
	printf("%ld %lu %s\n", diff, philo->id, type_str[activity]);
	pthread_mutex_unlock(&philo->main_struct->print);
}
