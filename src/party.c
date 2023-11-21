#include "../include/philo.h"

void* routine(void *ptr)
{
	t_philo	*temp;

	temp = (t_philo*)ptr;
	if (temp->id % 2)
		usleep(10);
	if (temp->limited_dinner)
	return (ptr);
}

void	start_the_party(t_main *main)
{
	__uint32_t	i;

	i = 0;
	gettimeofday(&main->time_start, NULL);
	while (i < main->num_of_philos)
	{
		if (pthread_create(&main->philos[i]->thread, NULL, &routine, main->philos[i]) != 0)
			error_exit("Failed to create thread\n");
		i++;
	}
}

void stop_the_party(t_main *main)
{
	__uint32_t	i;

	i = 0;
	while (i < main->num_of_philos)
	{
		pthread_join(main->philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < main->num_of_philos)
	{
		pthread_mutex_destroy(&main->philos[i]->r_fork);
		i++;
	}
	printf("after party\n");
}