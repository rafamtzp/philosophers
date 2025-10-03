/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafamtz <rafamtz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:45:32 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/03 15:59:05 by rafamtz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	int							time_to_eat;
	int							time_to_die;
	int							time_to_sleep;
	int							number_of_philosophers;
}								t_params;

typedef struct s_fork
{
	pthread_mutex_t				lock;
	int							id;
}								t_fork;

typedef struct s_grim_reaper	t_grim_reaper;

typedef struct s_philo
{
	struct timeval				starttime;
	t_fork						*l_fork;
	t_fork						*r_fork;
	struct s_grim_reaper		*reaper;
	int							id;
	pthread_t					thread_id;
	pthread_mutex_t				last_eaten_lock;
	long						last_eaten;
	int							time_to_die;
	int							meals_eaten;
}								t_philo;

typedef struct s_grim_reaper
{
	long						starttime;
	t_params					params;
	t_philo						*philos;
	t_fork						*forks;
	pthread_mutex_t				printlock;
	pthread_t					thread_id;
	bool						end_sim;
}								t_grim_reaper;

typedef struct s_thread_arg
{
	t_grim_reaper				*reaper;
	t_philo						*philo;
}								t_thread_arg;

/* helpers */
int								ft_atoi(const char *nptr);
void							print_status(t_grim_reaper *reaper,
									unsigned int philo_id, char msg);
long							get_time_in_ms(void);
long							get_rel_time_in_ms(long starttime);
void							safe_lock(pthread_mutex_t *mutex,
									t_grim_reaper *reaper);

/* init */
t_philo							*philos_init(t_params params, t_fork *forks);
t_fork							*forks_init(t_params params);
void							store_data(t_params *params, char **argv);

/* philo actions */
void							eat_and_sleep(t_grim_reaper *reaper,
									t_philo *philo);
void							philo_sleep(t_grim_reaper *reaper, long limit);
void							philo_think(t_grim_reaper *reaper,
									t_philo *philo);

/* exit */
int								handle_err(int err, t_grim_reaper *reaper);
void							free_all(t_grim_reaper *reaper);
void							destroy_mutexes(t_grim_reaper *reaper);

#endif