#include "../include/philo.h"

static void	no_limit_meals(char **argv, t_main **main)
{
	if (ft_atoui32(argv[0]) > 200)
		error_exit("Pass a number of philos between 1 and 200");
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->limited_dinner = false;
}

static void	limited_meals(char **argv, t_main **main)
{
	if (ft_atoui32(argv[0]) > 200)
		error_exit("Pass a number of philos between 1 and 200\n");
	if (ft_atoui32(argv[4]) <= 0)
		error_exit("Pass a number greater than 0\n");
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->number_of_meals = ft_atoui32(argv[4]);
	(*main)->limited_dinner = true;
}

static void	split_args(char *argv, t_main **main)
{
	char	**temp_args;
	int		i;

	i = 0;
	temp_args = check_malloc(ft_split(argv, ' '));
	while (temp_args[i])
		i++;
	if (i == 4)
		no_limit_meals(temp_args, main);
	else if (i == 5)
		limited_meals(temp_args, main);
	else
		error_exit("Incorrect input\n");
	double_free(temp_args);
}

void	get_input(t_main **main, char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		split_args(*argv, main);
	else if (i == 4)
		no_limit_meals(argv, main);
	else if (i == 5)
		limited_meals(argv, main);
	else
		error_exit("Incorrect input\n");
	if (pthread_mutex_init(&(*main)->print, NULL))
		error_exit("mutex failure");
}
