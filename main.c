/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:45:11 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/08 15:44:49 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_grim_reaper	reaper;
	int				i;

	if (is_valid_input(argc, argv) == false)
		return (handle_err(0, &reaper));
	store_data(&reaper.params, argc, argv);
	reaper.forks = forks_init(reaper.params);
	if (!reaper.forks)
		return (handle_err(1, &reaper));
	reaper.philos = philos_init(reaper.params, reaper.forks);
	if (!reaper.philos)
		return (handle_err(1, &reaper));
	if (start_threads(&reaper) == -1)
		return (handle_err(2, &reaper));
	pthread_join(reaper.thread_id, NULL);
	i = 0;
	while (i < reaper.params.number_of_philosophers)
	{
		pthread_join(reaper.philos[i].thread_id, NULL);
		i++;
	}
	destroy_mutexes(&reaper);
	free_all(&reaper);
}
