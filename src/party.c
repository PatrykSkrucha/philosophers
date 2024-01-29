#include "../include/philo.h"

void	*routine(void *ptr)
{
	t_philo	*temp;

	temp = ptr;
	if (temp->id % 2 == 0)
		print_message(temp, 2);
	//if (temp->limited_dinner)
	return (ptr);
}

//void*	monitoring(void *ptr)
//{
//	t_philo	*temp;

//	temp = (t_philo*)ptr;

//}

void	start_simulation(t_main *main)
{
	__uint32_t	i;
	//pthread_t	monitor;

	i = 0;
	main->time_start = get_time();
	while (i < main->num_of_philos)
	{
		//printf("start at: %ld\n", get_time() - main->time_start);
		if (pthread_create(&main->philos[i]->thread, NULL, &routine, main->philos[i]) != 0)
			error_exit("Failed to create thread\n");
		i++;
	}
	//if (pthread_create(&monitor, NULL, &monitoring, main->philos) != 0)
	//	thread_error();
	//if (pthread_join(monitor, NULL) != 0)
	//	thread_error();
}

void stop_simulation(t_main *main)
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

}