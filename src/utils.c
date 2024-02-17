/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:09:29 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 16:31:30 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
}

void	ft_sleep(t_philo *philo, long value)
{
	long	start_time;
	long	time_lap;

	start_time = get_time();
	time_lap = get_time() - start_time;
	while (time_lap < value)
	{
		if (get_status(philo) != ALIVE)
			return ;
		usleep(50);
		time_lap = get_time() - start_time;
	}
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (str1[i] == str2[i] && (str1[i] != '\0' && str2[i] != '\0')
		&& i < n - 1)
	{
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

int	precheck(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (ft_strlen(argv[i]) == 0)
		{
			print_error("Incorrect input\n");
			return (1);
		}
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				print_error("Incorrect input\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
