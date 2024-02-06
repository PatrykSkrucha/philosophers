#include "../include/philo.h"

static void	hand_out_forks(t_main **main)
{
	__uint32_t	i;

	i = 0;
	while (i < (*main)->num_of_philos)
	{
		pthread_mutex_init(&(*main)->philos[i]->r_fork, NULL);
		i++;
	}
	i = 0;
	while (i < (*main)->num_of_philos - 1)
	{
		(*main)->philos[i]->l_fork = &(*main)->philos[i + 1]->r_fork;
		i++;
	}
	if (i == 0)
		return ;
	(*main)->philos[i]->l_fork = &(*main)->philos[0]->r_fork;
}

void	invite_philos(t_main **main)
{
	__uint32_t	i;

	i = 0;
	(*main)->philos = check_malloc(malloc(sizeof(t_philo *) * \
						(*main)->num_of_philos));
	while (i < (*main)->num_of_philos)
	{
		(*main)->philos[i] = check_malloc(malloc(sizeof(t_philo)));
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
		i++;
	}
	hand_out_forks(main);
}
