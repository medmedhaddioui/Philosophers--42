/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/10 20:29:01 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_philo *arg, t_program *program)
{
    int i;
    i = 0;
    arg->mutexs = malloc (sizeof(pthread_mutex_t) * arg->nb_of_philos);
    if (!arg->mutexs)
        return 1;
    while (i < arg->nb_of_philos)
		pthread_mutex_init(&arg->mutexs[i++], NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    return 0;
}
void init_arg(int i, t_philo *philos,t_philo arg)
{
    philos[i].time_to_die = arg.time_to_die;
    philos[i].time_to_eat = arg.time_to_eat;
    philos[i].time_to_sleep = arg.time_to_sleep;
    philos[i].nb_times_to_eat = arg.nb_times_to_eat;
}
void init_philo (t_philo *philos, t_philo arg, t_program *program)
{
    int i;
    i = 0;
    while (i < arg.nb_of_philos)
    {
        philos[i].philo_id = i + 1;
        init_arg(i, philos, arg);
        philos[i].died = 0;
        philos[i].eating_count = 0; 
        philos[i].start_time = get_current_time_ms();
        philos[i].time = 0;
        philos[i].first_fork = &arg.mutexs[i];
        philos[i].write_lock = &program->write_lock;
        philos[i].meal_lock = &program->meal_lock;
        philos[i].dead_lock = &program->dead_lock;
        program->dead_flag = 0;
        if (i == arg.nb_of_philos - 1)
            philos[i].second_fork = &arg.mutexs[0];
        else
            philos[i].second_fork = &arg.mutexs[i + 1];
        i++;
        program->philos = philos;
    }
}