/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafamtz <rafamtz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:33:09 by rafamtz           #+#    #+#             */
/*   Updated: 2025/10/03 16:50:30 by rafamtz          ###   ########.fr       */
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

	if (argc != 5)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200)
			return (false);
		i++;
	}
	return (true);
}
