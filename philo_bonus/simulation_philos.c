/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/23 20:36:54 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*ft_check_death(void *data)
{
    t_philo *philo = data;
    while (1)
    {
        sem_wait(philo->dead);
        if (get_current_time_ms () - philo->last_meal > philo->time_to_die )
        {
            sem_wait(philo->write);
            printf("%ld %d is dead\n", philo->time, philo->philo_id);
            ft_exit2(philo);
        }
        sem_post(philo->dead);
    }

    return NULL;
}
void routine (t_philo *philo)
{
    pthread_t check_death;
    pthread_create(&check_death, NULL, &ft_check_death, (void *) philo);
    if (philo->philo_id % 2 != 0)
        ft_usleep(1);
    while (1)
    {
        if (philo->flag == EAT_COUNT_ON && philo->nb_times_to_eat == philo->eating_count)
            exit(EXIT_SUCCESS);
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
}
void simulation_philos (t_philo *philos, t_program *prog)
{
    int i;
    i = 0;
    while (i < prog->nb_philos)
    {
        prog->id = fork();
        if (prog->id == 0)
        {
            routine(&philos[i]);
            exit(EXIT_SUCCESS);
        }
        prog->pids[i] = prog->id;
        i++;
    }
    i = -1;
    int	status;
	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
            i = 0;
		    while (i < prog->nb_philos)
	        {
		        kill(prog->pids[i], SIGKILL);
		        i++;
            }
		}
	}
    sem_cleanup(&philos[0]);
}