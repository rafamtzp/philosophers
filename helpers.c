/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:23 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/07 19:23:01 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_lock(pthread_mutex_t *mutex, t_grim_reaper *reaper)
{
	if (sim_stopped(reaper) == false)
	{
		if (pthread_mutex_lock(mutex) != 0)
		{
			pthread_mutex_lock(&reaper->end_lock);
			reaper->end_sim = true;
			pthread_mutex_unlock(&reaper->end_lock);
		}
	}
}

bool	sim_stopped(t_grim_reaper *reaper)
{
	bool result;

	result = false;
	pthread_mutex_lock(&reaper->end_lock);
	if (reaper->end_sim == true)
		result = true;
	pthread_mutex_unlock(&reaper->end_lock);
	return (result);
}

long	get_time_in_ms(void)
{
	struct timeval	now;
	long			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000 + now.tv_usec / 1000);
	return (time);
}

long	get_rel_time_in_ms(long starttime)
{
	return (get_time_in_ms() - starttime);
}

void	print_status(t_grim_reaper *reaper, unsigned int philo_id, char msg)
{
	long	time;

	if (sim_stopped(reaper) == true)
		return ;
	safe_lock(&reaper->printlock, reaper);
	if (sim_stopped(reaper) == true)
		return ;
	time = get_time_in_ms() - reaper->starttime;
	if (msg == 'f')
		printf("%ld %u has taken a fork\n", time, philo_id + 1);
	else if (msg == 'e')
		printf("%ld %u is eating\n", time, philo_id + 1);
	else if (msg == 's')
		printf("%ld %u is sleeping\n", time, philo_id + 1);
	else if (msg == 't')
		printf("%ld %u is thinking\n", time, philo_id + 1);
	else if (msg == 'd')
	{
		printf("%ld %u died\n", time, philo_id + 1);
		pthread_mutex_lock(&reaper->end_lock);
		reaper->end_sim = true;
		pthread_mutex_unlock(&reaper->end_lock);
	}
	pthread_mutex_unlock(&reaper->printlock);
}
