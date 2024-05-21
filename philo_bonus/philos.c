/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/20 17:09:38 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void routine (t_philo *philo)
{
    eating();
    sleeping();
    thinking();
}

void make_philos (t_philo *philos, t_program *prog , int ac)
{
    int i;
    i = 0;
    while (i < prog->nb_philos)
    {
        prog->id = fork();
        if (prog->id == 0)
            routine(&philos[i]);
        i++;
    }
}