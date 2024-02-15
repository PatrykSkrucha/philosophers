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

//typedef struct print
//{
//	void (*print_eat)(t_philo*, long);
//	void (*print_sleep)(t_philo*, long);
//	void (*print_fork)(t_philo*, long);
//	void (*print_death)(t_philo*, long);
//} 	t_print;

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

int	set_mutex(t_main **main)
{
	__uint32_t	i;

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
	if (pthread_mutex_init(&(*main)->print, NULL))
	{
			destroy_mutex_status(*main, (*main)->num_of_philos, (*main)->num_of_philos);
			return (1);
	}
	if (hand_out_forks(main))
		return (1);
	return (0);
}

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

//void	print_message(t_philo *philo, t_activity activity)
//{
//	long		diff;
//	//Print		jp_tab[4];

//	void (*jp_tab[5])(); // Declare an array of function pointers

//// Initialize each element of the array with the corresponding function
//	jp_tab[0] = print_eat;
//	jp_tab[1] = print_sleep;
//	jp_tab[2] = print_fork;
//	jp_tab[3] = print_death;
//	jp_tab[4] = print_think;
//	//*jp_tab = {print_eat, print_sleep, print_fork, print_death};
//	//t_print		*print;

//	if (get_status(philo) != ALIVE)
//		return ;
//	//print = check_malloc(malloc(sizeof(t_print) * 4));
//	diff = get_time() - philo->main_struct->time_start;
//	printf("%ld %lu ", diff, philo->id);
//	jp_tab[activity]();

//	//if (activity == DEATH)
//	//	printf("%ld %lu died\n", diff, philo->id);
//	//if (activity == EAT && get_status(philo) == ALIVE)
//	//	printf("%ld %lu is eating\n", diff, philo->id);
//	//else if (activity == SLEEP && get_status(philo) == ALIVE)
//	//	printf("%ld %lu is sleeping\n", diff, philo->id);
//	//else if (activity == THINK && get_status(philo) == ALIVE)
//	//	printf("%ld %ld is thinking\n", diff, philo->id);
//	//else if (activity == FORK && get_status(philo) == ALIVE)
//	//	printf("%ld %lu has taken a fork\n", diff, philo->id);
//}

void	print_message(t_philo *philo, t_activity activity)
{
	long		diff;
	const char	*type_str[] = {
	[EAT] = "is eating",
	[SLEEP] = "is sleeping",
	[FORK] = "has taken a fork",
	[THINK] = "is thinking",
	};
	diff = get_time() - philo->main_struct->time_start;
	pthread_mutex_lock(&philo->main_struct->print);
	if (get_status(philo) != ALIVE)
	{
		pthread_mutex_unlock(&philo->main_struct->print);
		return ;
	}
	printf("%ld %lu %-12s\n", diff,philo->id ,type_str[activity]);
	pthread_mutex_unlock(&philo->main_struct->print);
}