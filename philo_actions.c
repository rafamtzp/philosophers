/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:11 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/07 20:25:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_grim_reaper *reaper, t_philo *philo)
{
	if (sim_stopped(reaper) == true)
		return ;
	if (philo->id % 2 == 0)
	{
		safe_lock(&philo->r_fork->lock, reaper);
		print_status(reaper, philo->id, 'f');
		if (reaper->params.number_of_philosophers > 1)
		{
			safe_lock(&philo->l_fork->lock, reaper);
			print_status(reaper, philo->id, 'f');
		}
	}
	else
	{
		safe_lock(&philo->l_fork->lock, reaper);
		print_status(reaper, philo->id, 'f');
		safe_lock(&philo->r_fork->lock, reaper);
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

void	philo_think(t_grim_reaper *reaper, t_philo *philo)
{
	long	wake_up;
	long	limit;
	long	now;

	print_status(philo->reaper, philo->id, 't');
	limit = reaper->params.time_to_die - (get_rel_time_in_ms(reaper->starttime)
			- philo->last_eaten) - (reaper->params.time_to_eat / 2);
	if (limit < 0)
		return ;
	else if (limit > 600)
		limit = 200;
	now = get_rel_time_in_ms(reaper->starttime);
	wake_up = get_rel_time_in_ms(reaper->starttime) + limit;
	while (now < wake_up)
	{
		now = get_rel_time_in_ms(reaper->starttime);
		usleep(100);
		if (sim_stopped(reaper) == true)
			return ;
	}
}

void	philo_sleep(t_grim_reaper *reaper, long limit)
{
	long	wake_up;
	long	now;

	now = get_rel_time_in_ms(reaper->starttime);
	wake_up = get_rel_time_in_ms(reaper->starttime) + limit;
	while (now < wake_up)
	{
		now = get_rel_time_in_ms(reaper->starttime);
		usleep(100);
		if (sim_stopped(reaper) == true)
			return ;
	}
}

void	eat_and_sleep(t_grim_reaper *reaper, t_philo *philo)
{
	take_forks(reaper, philo);
	while (reaper->params.number_of_philosophers == 1)
	{
		if (sim_stopped(reaper) == true)
			return ;
	}
	print_status(reaper, philo->id, 'e');
	safe_lock(&philo->last_eaten_lock, reaper);
	philo->last_eaten = get_rel_time_in_ms(reaper->starttime);
	pthread_mutex_unlock(&philo->last_eaten_lock);
	philo_sleep(reaper, reaper->params.time_to_eat);
	drop_forks(philo);
	print_status(reaper, philo->id, 's');
	philo_sleep(reaper, reaper->params.time_to_sleep);
}
