#include "philo.h"

// destroy mutexes


// free philos and forks (also destroys mutexes)
void free_all()
{
    // free philosophers

    // destroy mutexes (forks)

    // free forks
}

int handle_err(int err, grim_reaper_t *reaper)
{
	if (err == 0)
	{
		printf("Error.\nUsage: NUM_PHILOSOPHERS(>=1)");
		printf("TIME_TO_DIE EATING_TIME SLEEPING_TIME\n");
		printf("(all in miliseconds)\n");
	}
    else if (err == 1)
        printf("Error: Unable to allocate memory\n");
    else if (err == 2)
    {
        printf("Error: Unable to create threads\n");
        free_all(reaper->philos, reaper->forks);
    }
    return (-1);
}





