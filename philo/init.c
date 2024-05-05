/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/05 21:10:01 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_philo arg)
{
    pthread_mutex_t mutexs[arg.nb_of_philos];
    int i;
    i = 0;
    while (i < arg.nb_of_philos)
	{
		pthread_mutex_init(&mutexs[i], NULL);
		i++;
	}
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
        philos[i].last_meal_time = get_current_time_ms();
        i++;
    }
}
