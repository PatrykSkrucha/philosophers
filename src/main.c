#include "../include/philo.h"

int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void* nic(void *ptr)
{
	int index = *(int*)ptr;
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += numbers[index + i];
	}
	*(int*)ptr = sum;
	return (ptr);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t		philo[2];
	int i = 0;
	int	*a;
	int sum = 0;
	int *status;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		//*a *= 5;
		if (pthread_create(&philo[i], NULL, &nic, a) != 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(philo[i], (void**)&status);
		sum += *status;
		free(status);
		i++;
	}
	printf("sum %d\n", sum);
	return (0);
}