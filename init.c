/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:46:38 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/07 20:26:03 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	store_data(t_params *params, char **argv)
{
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
}

t_fork	*forks_init(t_params params)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * params.number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < params.number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i].lock, NULL) != 0)
			return (NULL);
		forks[i].id = i;
		i++;
	}
	return (forks);
}

t_philo	*philos_init(t_params params, t_fork *forks)
{
	int				i;
	t_philo			*philos;
	unsigned int	n;

	n = params.number_of_philosophers;
	philos = malloc(sizeof(t_philo) * params.number_of_philosophers);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < params.number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].time_to_die = params.time_to_die;
		philos[i].last_eaten = 0;
		pthread_mutex_init(&philos[i].last_eaten_lock, NULL);
		if (i == 0)
			philos[i].l_fork = &forks[n - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		philos[i].r_fork = &forks[i];
		i++;
	}
	return (philos);
}
