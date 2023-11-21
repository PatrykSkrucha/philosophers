#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_main	*main;

	if (argc < 2)
	{
		printf("Too few arguments\n");
		exit (1);
	}
	main = arrange_main(++argv);
	start_the_party(main);
	//exit(1);
	stop_the_party(main);
	free_main(main);
	return (0);
}
