/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:57:14 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/08 16:57:15 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	all_done_eating(t_grim_reaper *reaper, t_params params)
{
	bool	ret;
	int		i;

	ret = true;
	i = 0;
	if (params.meal_limit == -1)
		return (false);
	while (i < params.number_of_philosophers)
	{
		if (reaper->philos[i].meals_eaten < params.meal_limit)
		{
			ret = false;
			break ;
		}
		i++;
	}
	if (ret == true)
	{
		safe_lock(&reaper->end_lock, reaper);
		reaper->end_sim = true;
		pthread_mutex_unlock(&reaper->end_lock);
	}
	return (ret);
}

static void	try_to_end_sim(long time_passed, t_grim_reaper *reaper, int i)
{
	if (time_passed >= reaper->params.time_to_die)
		print_status(reaper, i, 'd');
	else if (all_done_eating(reaper, reaper->params) == true)
	{
		safe_lock(&reaper->printlock, reaper);
		printf("All philosophers are done eating\n");
		pthread_mutex_unlock(&reaper->printlock);
	}
	return ;
}

void	*reaper_routine(void *ptr)
{
	t_grim_reaper	*reaper;
	int				i;
	long			time_passed;
	long			now;

	reaper = ptr;
	delay_start(reaper->starttime);
	now = 0;
	time_passed = 0;
	while (1)
	{
		i = 0;
		while (i < reaper->params.number_of_philosophers)
		{
			safe_lock(&reaper->philos[i].last_eaten_lock, reaper);
			now = get_rel_time_in_ms(reaper->starttime);
			time_passed = now - reaper->philos[i].last_eaten;
			try_to_end_sim(time_passed, reaper, i);
			pthread_mutex_unlock(&reaper->philos[i].last_eaten_lock);
			if (sim_stopped(reaper) == true)
				return (NULL);
			i++;
		}
	}
}
