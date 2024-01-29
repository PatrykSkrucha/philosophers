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

long	ft_atoui32(char *str)
{
	long	number;

	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		error_exit("Type positive number\n");
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (number);
}

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
