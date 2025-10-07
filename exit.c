/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:05 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/07 19:48:22 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_grim_reaper *reaper)
{
	int	i;

	i = 0;
	while (i < reaper->params.number_of_philosophers)
	{
		pthread_mutex_destroy(&reaper->philos[i].last_eaten_lock);
		pthread_mutex_destroy(&reaper->forks[i++].lock);
	}
	pthread_mutex_destroy(&reaper->printlock);
}

void	free_all(t_grim_reaper *reaper)
{
	free(reaper->philos);
	free(reaper->forks);
}

int	handle_err(int err, t_grim_reaper *reaper)
{
	if (err == 0)
	{
		printf("Error.\nUsage:\n./philo no_philos(>=1) ");
		printf("time_to_die time_to_eat time_to_sleep");
		printf(" (all in miliseconds)\n");
		printf("*No more than 200 philos nor times under 60ms\n");
	}
	else if (err == 1)
		printf("Error: Unable to allocate memory\n");
	else if (err == 2)
	{
		printf("Error: Unable to create threads\n");
		free_all(reaper);
	}
	return (-1);
}
