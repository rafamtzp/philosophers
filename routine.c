/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:57:23 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/08 17:01:52 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delay_start(long starttime)
{
	long	now;

	now = get_time_in_ms();
	while (now < starttime)
	{
		now = get_time_in_ms();
		usleep(100);
	}
}

static void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	delay_start(philo->reaper->starttime);
	if (philo->id % 2 == 0)
		philo_sleep(philo->reaper, 1);
	while (sim_stopped(philo->reaper) == false)
	{
		eat_and_sleep(philo->reaper, philo);
		philo_think(philo->reaper, philo);
	}
	return (NULL);
}

int	start_threads(t_grim_reaper *reaper)
{
	int				i;
	struct timeval	time;

	if (pthread_mutex_init(&reaper->printlock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&reaper->end_lock, NULL) != 0)
		return (-1);
	reaper->end_sim = false;
	gettimeofday(&time, NULL);
	reaper->starttime = time.tv_sec * 1000 + time.tv_usec / 1000
		+ reaper->params.number_of_philosophers * 20;
	i = 0;
	while (i < reaper->params.number_of_philosophers)
	{
		reaper->philos[i].reaper = reaper;
		if (pthread_create(&reaper->philos[i].thread_id, NULL, routine,
				&reaper->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&reaper->thread_id, NULL, reaper_routine, reaper) != 0)
		return (-1);
	return (0);
}
