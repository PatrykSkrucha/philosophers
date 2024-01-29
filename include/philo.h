#ifndef PHILO_H
# define  PHILO_H
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
	THINK,
	FORK,
	DEATH
}	t_activity;

typedef struct s_philo
{
	pthread_t		thread;
	struct s_main	*main_struct;
	t_status		status;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t r_fork;
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
	t_philo			**philos;
	long			time_start;
	pthread_mutex_t	print;
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_meals;
	bool			limited_dinner;
}	t_main;

void		*check_malloc(void *ptr);
t_main		*arrange_main(char **argv);
char    	**ft_split(char *str, char c);
long		ft_atoui32(char *str);
t_status	get_status(t_philo *philo);
int			ft_strlen(char	*str);
void		start_simulation(t_main *main);
void		stop_simulation(t_main *main);
void		error_exit(char *message);
void		free_main(t_main *main);
long		get_time(void);
void		print_message(t_philo *philo, t_activity activity);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);
void		ft_sleep(t_philo *philo, long value);
void		update_meal_time(t_philo *philo);
void		solo_dinner(t_main *main);
void*		monitoring(void *ptr);
void		get_input(t_main **main, char **argv);
void		double_free(char **str);
int			ft_strlen(char	*str);

#endif