/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/22 15:31:00 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void routine (t_philo *philo, t_program *prog)
{
    if (philo->philo_id % 2 != 0)
        ft_usleep(1);
    eating(philo, prog);
    sleeping(philo);
    thinking(philo);
}

// void	*ft_check_death(void *data)
// {
// 	t_program	*prog;
// 	int			i;
// 	size_t		time_die;

// 	prog = data;
// 	i = 0;
// 	time_die = prog->philos[0].time_to_die;
// 	while (time_check_lock(prog, i) <= time_die || check_full_lock(prog,
// 			i) == 1)
// 	{
// 		if (check_full_lock(prog, i))
// 		{
// 			if (check_other_philos_full(prog) == 1)
// 				return (NULL);
// 		}
// 		if (prog->nb_philos == i + 1)
// 			i = -1;
// 		i++;
// 	}
// 	pthread_mutex_lock(prog->philos[0].dead_lock);
// 	prog->dead_flag = 1;
// 	pthread_mutex_unlock(prog->philos[0].dead_lock);
// 	printf("%ld %d is Dead\n", time_die, prog->philos[i].philo_id);
// 	return (NULL);
// }

void simulation_philos (t_philo *philos, t_program *prog , int ac)
{
    (void) ac;
    
    int i;
    i = 0;
    while (i < prog->nb_philos)
    {
        prog->id = fork();
        if (prog->id == 0)
        {
            routine(&philos[i], prog);
            sem_cleanup(prog);
        }
        i++;
    }
    i = 0;
    while (i < prog->nb_philos)
    {
        wait(NULL);
        i++;
    }
   
}