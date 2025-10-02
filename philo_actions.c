#include "philo.h"

void take_forks(grim_reaper_t *reaper, philo_t *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->r_fork->lock);
        print_status(reaper, philo->id, 'f');
        pthread_mutex_lock(&philo->l_fork->lock);
        print_status(reaper, philo->id, 'f');
    }
    else
    {
        pthread_mutex_lock(&philo->l_fork->lock);
        print_status(reaper, philo->id, 'f');
        pthread_mutex_lock(&philo->r_fork->lock);
        print_status(reaper, philo->id, 'f');
    }
}

void drop_forks(philo_t *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->l_fork->lock);
        pthread_mutex_unlock(&philo->r_fork->lock);
    }
    else
    {
        pthread_mutex_unlock(&philo->r_fork->lock);
        pthread_mutex_unlock(&philo->l_fork->lock);
    }
}

void philo_think(grim_reaper_t *reaper, philo_t *philo)
{
    long wake_up;
    long limit;
    long now;

    limit = reaper->params.time_to_die - (get_time_in_ms() - reaper->starttime - philo->last_eaten)
    - (reaper->params.time_to_eat / 2);
    if (reaper->params.number_of_philosophers >= 100)
        limit = limit + (reaper->params.number_of_philosophers / 100);
    if (limit < 0)
        limit = 0;
    else if (limit > 600)
        limit = 200;
    now = get_time_in_ms() - reaper->starttime;
    wake_up = get_time_in_ms() - reaper->starttime + limit;
    while (now < wake_up)
    {
        now = get_time_in_ms() - reaper->starttime;
        usleep(100);
    }
}
void philo_sleep(grim_reaper_t *reaper, long limit)
{
    long wake_up;
    long now;

    now = get_time_in_ms() - reaper->starttime;
    wake_up = get_time_in_ms() - reaper->starttime + limit;
    while (now < wake_up)
    {
        now = get_time_in_ms() - reaper->starttime;
        usleep(100);
    }
}

void eat_and_sleep(grim_reaper_t *reaper, philo_t *philo)
{
    take_forks(reaper, philo);
    print_status(reaper, philo->id, 'e');
    pthread_mutex_lock(&philo->last_eaten_lock);
    philo->last_eaten = get_time_in_ms() - reaper->starttime;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->last_eaten_lock);
    philo_sleep(reaper, reaper->params.time_to_eat);
    drop_forks(philo);
    print_status(reaper, philo->id, 's');
    philo_sleep(reaper, reaper->params.time_to_sleep);
}

