#include "../include/philo.h"

void	error_exit(char *message)
{
	write(2, &message, ft_strlen(message));
	exit (1);
}

void	*check_malloc(void *ptr)
{
	if (!ptr)
		error_exit("Incorrect input\n");
	return (ptr);
}

__uint32_t	ft_atoui32(char *str)
{
	__uint32_t	number; 

	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	if (number <= 0)
		error_exit("Incorrect input\n");
	return (number);
}

void	no_limit_meals(char **argv, t_main **main)
{
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->limited_dinner = false;
}

void	limited_meals(char **argv, t_main **main)
{
	(*main)->num_of_philos = ft_atoui32(argv[0]);
	(*main)->time_to_die = ft_atoui32(argv[1]);
	(*main)->time_to_eat = ft_atoui32(argv[2]);
	(*main)->time_to_sleep = ft_atoui32(argv[3]);
	(*main)->number_of_meals = ft_atoui32(argv[4]);
	(*main)->limited_dinner = true;

}

void	split_args(char *argv, t_main **main)
{
	char	**temp_args;
	int		i;

	i = 0;
	printf("str:%s\n", argv);
	temp_args = check_malloc(ft_split(argv, ' '));
	while (temp_args[i])
		i++;
	if (i == 4)
		no_limit_meals(temp_args, main);
	else if (i == 5)
		limited_meals(temp_args, main);
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
}

void	call_philos(t_main **main)
{
	__uint32_t	i;

	i = 0;
	(*main)->philos = check_malloc(malloc(sizeof(t_philo*) * \
						(*main)->num_of_philos));
	while (i < (*main)->num_of_philos)
	{
		(*main)->philos[i] =check_malloc( malloc(sizeof(t_philo)));
		(*main)->philos[i]->id = i;
		(*main)->philos[i]->sim_start = &(*main)->time_start;
		(*main)->philos[i]->time_to_die = (*main)->time_to_die;
		(*main)->philos[i]->time_to_eat = (*main)->time_to_eat;
		(*main)->philos[i]->time_to_sleep = (*main)->time_to_sleep;
		i++;
	}

}

t_main	*arrange_main(char **argv)
{
	t_main	*main;

	main = check_malloc(malloc(sizeof(t_main)));
	get_input(&main, argv);
	call_philos(&main);
	gettimeofday(&main->time_start, NULL);
	printf("git\n");
	return (main);
}