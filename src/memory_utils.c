#include "../include/philo.h"

void	free_main(t_main *main)
{
	__uint32_t	i;

	i = 0;
	while (i < main->num_of_philos)
	{
		free(main->philos[i]);
		i++;
	}
	free(main->philos);
	free(main);
}