/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafamtz <rafamtz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:11 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/03 14:23:50 by rafamtz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_grim_reaper *reaper, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork->lock);
		print_status(reaper, philo->id, 'f');
		if (reaper->params.number_of_philosophers > 1)
		{
			pthread_mutex_lock(&philo->l_fork->lock);
			print_status(reaper, philo->id, 'f');
		}
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->lock);
		print_status(reaper, philo->id, 'f');
		pthread_mutex_lock(&philo->r_fork->lock);
		print_status(reaper, philo->id, 'f');
	}
}

void	drop_forks(t_philo *philo)
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

void	t_philohink(t_grim_reaper *reaper, t_philo *philo)
{
	long	wake_up;
	long	limit;
	long	now;

	limit = reaper->params.time_to_die - (get_rel_time_in_ms(reaper->starttime)
			- philo->last_eaten) - (reaper->params.time_to_eat / 2);
	if (reaper->params.number_of_philosophers >= 100)
		limit = limit + (reaper->params.number_of_philosophers / 100);
	if (limit < 0)
		limit = 0;
	else if (limit > 600)
		limit = 200;
	now = get_rel_time_in_ms(reaper->starttime);
	wake_up = get_rel_time_in_ms(reaper->starttime) + limit;
	while (now < wake_up && reaper->end_sim == false)
	{
		now = get_rel_time_in_ms(reaper->starttime);
		usleep(100);
	}
}

void	philo_sleep(t_grim_reaper *reaper, long limit)
{
	long	wake_up;
	long	now;

	now = get_rel_time_in_ms(reaper->starttime);
	wake_up = get_rel_time_in_ms(reaper->starttime) + limit;
	while (now < wake_up && reaper->end_sim == false)
	{
		now = get_rel_time_in_ms(reaper->starttime);
		usleep(100);
	}
}

void	eat_and_sleep(t_grim_reaper *reaper, t_philo *philo)
{
	take_forks(reaper, philo);
	while (reaper->params.number_of_philosophers == 1)
	{
		if (reaper->end_sim == true)
			return ;
	}
	print_status(reaper, philo->id, 'e');
	pthread_mutex_lock(&philo->last_eaten_lock);
	philo->last_eaten = get_rel_time_in_ms(reaper->starttime);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_eaten_lock);
	philo_sleep(reaper, reaper->params.time_to_eat);
	drop_forks(philo);
	print_status(reaper, philo->id, 's');
	philo_sleep(reaper, reaper->params.time_to_sleep);
}
