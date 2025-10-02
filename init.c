#include "philo.h"

void store_data(params_t *params, char **argv)
{
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
}
fork_t *forks_init(params_t params)
{
    fork_t *forks;
    int i;

	forks = malloc(sizeof(fork_t) * params.number_of_philosophers);
    if (!forks)
        return (NULL);
    i = 0;
    while (i < params.number_of_philosophers)
    {
        pthread_mutex_init(&forks[i].lock, NULL);
        forks[i].id = i;
        i++;
    }
    return (forks);
}
philo_t *philos_init(params_t params, fork_t *forks)
{
	int i;
    philo_t *philos;
    unsigned int N;

    N = params.number_of_philosophers;
    philos = malloc(sizeof(philo_t) * params.number_of_philosophers);
    if (philos == NULL)
        return (NULL);
	i = 0;
	while (i < params.number_of_philosophers)
	{
		philos[i].id = i;
        philos[i].meals_eaten = 0;
        philos[i].time_to_die = params.time_to_die;
        philos[i].meals_eaten = 0;
        philos[i].last_eaten = 0;
		pthread_mutex_init(&philos[i].last_eaten_lock, NULL);
        if (i == 0)
            philos[i].l_fork = &forks[N - 1];
        else
            philos[i].l_fork = &forks[i - 1];
        philos[i].r_fork = &forks[i];
        i++;
	}
    return (philos);
}
