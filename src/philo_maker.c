/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:06 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:09:09 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex_fork(t_main *main, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&main->philos[i]->r_fork);
		i--;
	}
}

int	hand_out_forks(t_main **main)
{
	__uint32_t	i;

	i = 0;
	while (i < (*main)->num_of_philos)
	{
		if (pthread_mutex_init(&(*main)->philos[i]->r_fork, NULL))
		{
			destroy_mutex_status(*main, (*main)->num_of_philos, (*main)->num_of_philos);
			destroy_mutex_fork(*main, i);
			pthread_mutex_destroy(&(*main)->print);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < (*main)->num_of_philos - 1)
	{
		(*main)->philos[i]->l_fork = &(*main)->philos[i + 1]->r_fork;
		i++;
	}
	if (i == 0)
		return (0);
	(*main)->philos[i]->l_fork = &(*main)->philos[0]->r_fork;
	return (0);
}

void	free_philos(int i, t_main *main)
{
	while (i >= 0)
	{
		free(main->philos[i]);
		i--;
	}
	free(main->philos);
	free(main);
}

void	pass_data_to_philo(t_main **main, int i)
{
	(*main)->philos[i]->id = i + 1;
	(*main)->philos[i]->time_to_die = (*main)->time_to_die;
	(*main)->philos[i]->time_to_eat = (*main)->time_to_eat;
	(*main)->philos[i]->time_to_sleep = (*main)->time_to_sleep;
	(*main)->philos[i]->status = ALIVE;
	(*main)->philos[i]->main_struct = (*main);
	if ((*main)->limited_dinner)
	{
		(*main)->philos[i]->limited_dinner = true;
		(*main)->philos[i]->number_of_meals = (*main)->number_of_meals;
	}
	else
		(*main)->philos[i]->limited_dinner = false;
}

int	invite_philos(t_main **main)
{
	__uint32_t	i;

	i = 0;
	(*main)->philos = malloc(sizeof(t_philo *) * (*main)->num_of_philos);
	if (!(*main))
	{
		print_error("Malloc failure\n");
		return (1);
	}
	while (i < (*main)->num_of_philos)
	{
		(*main)->philos[i] = malloc(sizeof(t_philo));
		if (!(*main)->philos[i])
		{
			free_philos(i, *main);
			return (1);
		}
		pass_data_to_philo(main, i);
		i++;
	}
	return (0);
}
