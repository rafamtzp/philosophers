#include "philo.h"

void delay_start(long starttime)
{
    long now;

    now = get_time_in_ms();
    while (now < starttime)
    {
        now = get_time_in_ms();
        usleep(100);
    }
}

void *reaper_routine(void *ptr)
{
    grim_reaper_t *reaper;
    int i;
    
    reaper = ptr;
    delay_start(reaper->starttime);
    while (1)
    {
        i = 0;
        while (i < reaper->params.number_of_philosophers)
        {
			pthread_mutex_lock(&reaper->philos[i].last_eaten_lock);
            if ((get_time_in_ms() - reaper->starttime - reaper->philos[i].last_eaten ) 
            >= reaper->params.time_to_die)
                print_status(reaper, reaper->philos[i].id, 'd');
            if (reaper->end_sim == true)
                return (NULL);
			pthread_mutex_unlock(&reaper->philos[i].last_eaten_lock);
            i++;
        }
    }

}

void *routine(void *ptr)
{
    philo_t *philo;

    philo = ptr;
    delay_start(philo->reaper->starttime);
    if (philo->id % 2 == 0)
        philo_sleep(philo->reaper, 1);
    while (philo->reaper->end_sim == false)
    {
        eat_and_sleep(philo->reaper, philo);
        print_status(philo->reaper, philo->id, 't');
        philo_think(philo->reaper, philo);
    }
    return (NULL);
}

int start_threads(grim_reaper_t *reaper)
{
    int i;
    struct timeval time;

	pthread_mutex_init(&reaper->printlock, NULL);
	reaper->end_sim = false;
    gettimeofday(&time, NULL);
    reaper->starttime =  time.tv_sec * 1000 + time.tv_usec / 1000 + reaper->params.number_of_philosophers * 20;
    i = 0;
	while (i < reaper->params.number_of_philosophers)
	{
		reaper->philos[i].reaper = reaper;
		if (pthread_create(&reaper->philos[i].thread_id, NULL, routine, &reaper->philos[i]) != 0)
			return (-1);
		i++;
	}
    if (pthread_create(&reaper->thread_id, NULL, reaper_routine, reaper) != 0)
        return (-1);
    return (0);
}

int main(int argc, char **argv)
{
	grim_reaper_t reaper;
    int i;

	if (argc != 5 || ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (handle_err(0));
	store_data(&reaper.params, argv);
	reaper.forks = forks_init(reaper.params);
    if (!reaper.forks)
        return (handle_err(1), &reaper);
	reaper.philos = philos_init(reaper.params, reaper.forks);
    if (!reaper.philos)
        return (handle_err(1), &reaper);
	if (start_threads(&reaper) == -1)
        return (handle_err(2), &reaper);
    pthread_join(reaper.thread_id, NULL);
	i = 0;
	while(i < reaper.params.number_of_philosophers)
	{
		pthread_join(reaper.philos[i].thread_id, NULL);
		i++;
    }
    free_all(&reaper);
    return (0);
}
