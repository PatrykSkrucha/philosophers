/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:23 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/13 13:43:50 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct timeval	t_timeval;

typedef enum e_status
{
	ALIVE,
	DEAD,
	FULLY_ATE
}	t_status;

typedef enum e_activity
{
	EAT,
	SLEEP,
	FORK,
	DEATH,
	THINK
}	t_activity;

typedef struct s_philo
{
	pthread_t		thread;
	struct s_main	*main_struct;
	t_status		status;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	long			id;
	long			last_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_meals;
	bool			limited_dinner;
}	t_philo;

typedef struct s_main
{
	pthread_mutex_t	print;
	t_philo			**philos;
	long			time_start;
	long			time_to_die;
	long			time_to_eat;
	long			num_of_philos;
	long			time_to_sleep;
	long			number_of_meals;
	bool			limited_dinner;
}	t_main;

long		get_time(void);
void		print_eat(void);
void		print_fork(void);
void		print_death(void);
void		print_think(void);
void		print_sleep(void);
void		eat(t_philo *philo);
int			ft_strlen(char	*str);
int			ft_strlen(char	*str);
long		ft_atoui32(char *str);
void		*monitoring(void *ptr);
void		double_free(char **str);
void		free_main(t_main *main);
void		*check_malloc(void *ptr);
void		exit_free(t_main **main);
void		error_exit(char *message);
void		solo_dinner(t_main *main);
void		print_error(char *message);
t_status	get_status(t_philo *philo);
t_main		*arrange_main(char **argv);
void		philo_sleep(t_philo *philo);
void		invite_philos(t_main **main);
void		stop_simulation(t_main *main);
char		**ft_split(char *str, char c);
void		start_simulation(t_main *main);
void		update_meal_time(t_philo *philo);
void		ft_sleep(t_philo *philo, long value);
void		get_input(t_main **main, char **argv);
void		print_message(t_philo *philo, t_activity activity);

#endif