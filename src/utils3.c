#include "../include/philo.h"

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

	diff = get_time() - philo->main_struct->time_start;
	if (activity == DEATH)
		printf("%ld %lu died\n", diff, philo->id);
	if (get_status(philo) != ALIVE)
		return ;
	if (activity == EAT)
		printf("%ld %lu is eating\n", diff, philo->id);
	else if (activity == SLEEP)
		printf("%ld %lu is sleeping\n", diff, philo->id);
	else if (activity == THINK)
	{
		printf("%ld %ld is thinking\n", diff, philo->id);
	}
	else if (activity == FORK)
		printf("%ld %lu has taken a fork\n", diff, philo->id);
}
