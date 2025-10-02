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

long get_time_in_ms(void)
{
    struct timeval now;
    long time;

    gettimeofday(&now, NULL);
    time = (now.tv_sec * 1000 + now.tv_usec / 1000);
    return (time);
}

void print_status(grim_reaper_t *reaper, unsigned int philo_id, char msg)
{
	long time;

	pthread_mutex_lock(&reaper->printlock);
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
		reaper->end_sim = true;
	}
	pthread_mutex_unlock(&reaper->printlock);
}

