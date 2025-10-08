/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:33:09 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/08 15:38:50 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	isminus;
	int	num;

	while (*nptr == ' ' || *nptr == '\r' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\v' || *nptr == '\n')
		nptr++;
	isminus = 0;
	if (*nptr == '-')
	{
		isminus = 1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num += (*nptr - '0');
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			num = num * 10;
	}
	if (isminus == 1)
		return (-num);
	return (num);
}

bool	is_valid_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1] < 1)
		return (false);
	i = 2;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (false);
		i++;
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (false);
	return (true);
}
