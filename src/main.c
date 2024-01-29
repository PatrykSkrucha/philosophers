#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc < 2)
	{
		printf("Too few arguments\n");
		exit (1);
	}
	main = arrange_main(++argv);
	if (main->num_of_philos == 1)
		solo_dinner(main);
	else
	{
		start_simulation(main);
		stop_simulation(main);
	}
	free_main(main);
	return (0);
}
