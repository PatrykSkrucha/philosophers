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

typedef void (*Print)(void);

void	set_mutex(t_main **main)
{
	__uint32_t	i;

	i = 0;
	while (i < (*main)->num_of_philos)
	{
		if (pthread_mutex_init(&(*main)->philos[i]->status_mutex, NULL))
			error_exit("mutex failure");
		i++;
	}
	i = 0;
	while (i < (*main)->num_of_philos)
	{
		if (pthread_mutex_init(&(*main)->philos[i]->time_mutex, NULL))
			error_exit("mutex failure");
		i++;
	}
}

t_main	*arrange_main(char **argv)
{
	t_main	*main;

	main = check_malloc(malloc(sizeof(t_main)));
	get_input(&main, argv);
	invite_philos(&main);
	set_mutex(&main);
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
	//Print		jp_tab[4];

	void (*jp_tab[5])(); // Declare an array of function pointers

// Initialize each element of the array with the corresponding function
	jp_tab[0] = print_eat;
	jp_tab[1] = print_sleep;
	jp_tab[2] = print_fork;
	jp_tab[3] = print_death;
	jp_tab[4] = print_think;
	//*jp_tab = {print_eat, print_sleep, print_fork, print_death};
	//t_print		*print;

	if (get_status(philo) != ALIVE)
		return ;
	//print = check_malloc(malloc(sizeof(t_print) * 4));
	diff = get_time() - philo->main_struct->time_start;
	printf("%ld %lu ", diff, philo->id);
	jp_tab[activity]();

	//if (activity == DEATH)
	//	printf("%ld %lu died\n", diff, philo->id);
	//if (activity == EAT && get_status(philo) == ALIVE)
	//	printf("%ld %lu is eating\n", diff, philo->id);
	//else if (activity == SLEEP && get_status(philo) == ALIVE)
	//	printf("%ld %lu is sleeping\n", diff, philo->id);
	//else if (activity == THINK && get_status(philo) == ALIVE)
	//	printf("%ld %ld is thinking\n", diff, philo->id);
	//else if (activity == FORK && get_status(philo) == ALIVE)
	//	printf("%ld %lu has taken a fork\n", diff, philo->id);
}
