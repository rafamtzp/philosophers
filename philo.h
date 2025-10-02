#ifndef PHILO_H
#define PHILO_H
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef pthread_mutex_t mutex_t;
typedef struct timeval timeval_t;

typedef struct
{
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int number_of_philosophers;
}	params_t;

typedef struct
{
    pthread_mutex_t lock;
    int id;
} fork_t;

typedef struct grim_reaper_s grim_reaper_t;

typedef struct
{
	struct timeval starttime;
	fork_t *l_fork;
	fork_t *r_fork;
	struct grim_reaper_s *reaper;
    int id;
	pthread_t thread_id;
	pthread_mutex_t last_eaten_lock;
	long last_eaten;
	int time_to_die;
	int meals_eaten;
}	philo_t;

typedef struct grim_reaper_s
{
	long starttime;
	params_t params;
	philo_t *philos;
    fork_t *forks;
	pthread_mutex_t printlock;
    pthread_t thread_id;
	bool end_sim;
}	grim_reaper_t;

typedef struct
{
	grim_reaper_t *reaper;
	philo_t *philo;
} thread_arg_t;

/* helpers */
int	ft_atoi(const char *nptr);

/*init*/
philo_t *philos_init(params_t params, fork_t *forks);
fork_t *forks_init(params_t params);
void store_data(params_t *params, char **argv);

#endif