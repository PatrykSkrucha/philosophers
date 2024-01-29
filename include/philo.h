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

typedef struct s_philo
{
	pthread_t		thread;
	struct s_main	*main_struct;
	t_status		status;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t r_fork;
	pthread_mutex_t	*l_fork;
	__uint32_t		id;
	__uint32_t		last_eat;
	__uint32_t		time_to_die;
	__uint32_t		time_to_eat;
	__uint32_t		time_to_sleep;
	__uint32_t		number_of_meals;
	bool			limited_dinner;
}	t_philo;

typedef struct s_main
{
	t_philo		**philos;
	long			time_start;
	pthread_mutex_t	print;
	__uint32_t		num_of_philos;
	__uint32_t		time_to_die;
	__uint32_t		time_to_eat;
	__uint32_t		time_to_sleep;
	__uint32_t		number_of_meals;
	bool			limited_dinner;
}	t_main;

void		*check_malloc(void *ptr);
t_main		*arrange_main(char **argv);
char    	**ft_split(char *str, char c);
__uint32_t	ft_atoui32(char *str);
int			ft_strlen(char	*str);
void		start_simulation(t_main *main);
void		stop_simulation(t_main *main);
void		error_exit(char *message);
void		free_main(t_main *main);
long		get_time(void);
void		print_message(t_philo *philo, int action);

#endif