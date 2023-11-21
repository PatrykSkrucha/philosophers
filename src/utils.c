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

void	double_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
}

void	hand_out_forks(t_main **main)
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
	(*main)->philos = check_malloc(malloc(sizeof(t_philo*) * \
						(*main)->num_of_philos));
	while (i < (*main)->num_of_philos)
	{
		(*main)->philos[i] =check_malloc( malloc(sizeof(t_philo)));
		(*main)->philos[i]->id = i + 1;
		(*main)->philos[i]->sim_start = &(*main)->time_start;
		(*main)->philos[i]->time_to_die = (*main)->time_to_die;
		(*main)->philos[i]->time_to_eat = (*main)->time_to_eat;
		(*main)->philos[i]->time_to_sleep = (*main)->time_to_sleep;
		(*main)->philos[i]->status = ALIVE;
		if ((*main)->limited_dinner)
		{
			(*main)->philos[i]->limited_dinner = true;
			(*main)->philos[i]->number_of_meals = (*main)->number_of_meals;
		}
		i++;
	}
	hand_out_forks(main);
}

t_main	*arrange_main(char **argv)
{
	t_main	*main;

	main = check_malloc(malloc(sizeof(t_main)));
	get_input(&main, argv);
	invite_philos(&main);
	return (main);
}