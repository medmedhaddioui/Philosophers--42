/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/22 14:26:32 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void routine (t_philo *philo, t_program *prog)
{
    eating(philo, prog);
    sleeping(philo);
    thinking(philo);
    exit(1);
}

void sem_cleanup(t_program *prog)
 {
    if (sem_close(prog->semaphore) == -1)
        ft_exit("Error closing semaphore");
}

void philosophers (t_philo *philos, t_program *prog , int ac)
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
    wait(NULL);
}