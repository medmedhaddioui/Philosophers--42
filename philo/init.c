/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/18 12:17:53 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_philo *arg, t_program *program)
{
	int	i;

	i = 0;
	while (i < arg->nb_of_philos)
		pthread_mutex_init(&arg->mutexs[i++], NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->full_lock, NULL);
	return (0);
}

void	init_arg_philo(int i, t_philo *philos, t_philo arg, int ac)
{
	philos[i].philo_id = i + 1;
	philos[i].time_to_die = arg.time_to_die;
	philos[i].time_to_eat = arg.time_to_eat;
	philos[i].time_to_sleep = arg.time_to_sleep;
	if (ac == 6)
	{
		philos[i].nb_times_to_eat = arg.nb_times_to_eat;
		philos[i].flag = EAT_COUNT_ON;
		philos[i].full = 0;
	}
	else
	{
		philos[i].flag = EAT_COUNT_OFF;
		philos[i].full = 0;
	}
}

void	init_program(t_program *program, t_philo *philos, t_philo arg)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->nb_philos = arg.nb_of_philos;
}

void	init_philo(t_philo *philos, t_philo arg, t_program *program, int ac)
{
	int	i;

	i = 0;
	while (i < arg.nb_of_philos)
	{
		init_arg_philo(i, philos, arg, ac);
		philos[i].eating_count = 0;
		philos[i].start_time = get_current_time_ms();
		philos[i].time = 0;
		philos[i].last_meal = get_current_time_ms();
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].full_lock = &program->full_lock;
		philos[i].died = &program->dead_flag;
		philos[i].l_fork = &arg.mutexs[i];
		if (i == arg.nb_of_philos - 1)
			philos[i].r_fork = &arg.mutexs[0];
		else
			philos[i].r_fork = &arg.mutexs[i + 1];
		i++;
	}
	init_program(program, philos, arg);
}
