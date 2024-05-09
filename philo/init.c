/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/09 16:10:04 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_philo *arg)
{
    int i;
    i = 0;
    arg->mutexs = malloc (sizeof(pthread_mutex_t) * arg->nb_of_philos);
    if (!arg->mutexs)
        return 1;
    while (i < arg->nb_of_philos)
		pthread_mutex_init(&arg->mutexs[i++], NULL);
    pthread_mutex_init(&arg->write_lock, NULL);
    pthread_mutex_init(&arg->meal_lock, NULL);
    pthread_mutex_init(&arg->dead_lock, NULL);
    return 0;
}

void init_philo (t_philo *philos, t_philo arg)
{
    int i;
    i = 0;
    while (i < arg.nb_of_philos)
    {
        philos[i].philo_id = i + 1;
        philos[i].time_to_die = arg.time_to_die;
        philos[i].time_to_eat = arg.time_to_eat;
        philos[i].time_to_sleep = arg.time_to_sleep;
        philos[i].nb_times_to_eat = arg.nb_times_to_eat;
        philos[i].start_time = get_current_time_ms();
        philos[i].last_meal_time = 0;
        philos[i].dead = 0;
        philos[i].first_fork = &arg.mutexs[i];
        philos[i].dead_lock = arg.dead_lock;
        philos[i].write_lock = arg.dead_lock;
        philos[i].meal_lock = arg.dead_lock;
        if (i == arg.nb_of_philos - 1)
            philos[i].second_fork = &arg.mutexs[0];
        else
            philos[i].second_fork = &arg.mutexs[i + 1];
        i++;
    }
   
}

