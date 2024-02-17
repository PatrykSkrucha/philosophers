/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:23 by pskrucha          #+#    #+#             */
/*   Updated: 2024/02/17 16:24:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef enum e_status
{
	DEAD,
	ALIVE,
	FULLY_ATE
}	t_status;

typedef enum e_activity
{
	EAT,
	FORK,
	SLEEP,
	DEATH,
	THINK
}	t_activity;

typedef struct s_philo
{
	long			id;
	pthread_t		thread;
	t_status		status;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	long			last_eat;
	pthread_mutex_t	time_mutex;
	long			time_to_die;
	long			time_to_eat;
	pthread_mutex_t	status_mutex;
	struct s_main	*main_struct;
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
	bool			limited_dinner;
	long			number_of_meals;
}	t_main;

long		get_time(void);
void		eat(t_philo *philo);
int			precheck(char **argv);
int			ft_strlen(char	*str);
int			ft_strlen(char	*str);
long		ft_atoui32(char *str);
void		*monitoring(void *ptr);
void		free_main(t_main *main);
int			set_mutex(t_main **main);
void		exit_free(t_main **main);
void		solo_dinner(t_main *main);
int			print_error(char *message);
t_status	get_status(t_philo *philo);
t_main		*arrange_main(char **argv);
void		philo_sleep(t_philo *philo);
int			invite_philos(t_main **main);
int			hand_out_forks(t_main **main);
int			start_simulation(t_main *main);
void		free_philos(int i, t_main *main);
void		update_meal_time(t_philo *philo);
void		join_and_free(t_main *main, int i);
void		ft_sleep(t_philo *philo, long value);
int			get_input(t_main **main, char **argv);
void		destroy_mutex_fork(t_main *main, int i);
void		destroy_mutex_status(t_main *main, int i, int j);
void		print_message(t_philo *philo, t_activity activity);

#endif