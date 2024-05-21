/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/21 16:51:02 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void routine (t_philo *philo, t_program *prog)
{
    // if (philo->philo_id % 2 != 0)
    //     usleep(1);
    eating(philo, prog);
    sleeping(philo);
    thinking(philo);
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
            exit(1);
        }
        i++;
    }
    
}