/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/22 13:50:48 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sem_create(t_program *prog, t_philo arg)
{
	sem_unlink("semaphore");
	prog->semaphore = sem_open("semaphore", O_CREAT | O_EXCL , 0644, arg.nb_of_philos);
	if (prog->semaphore == SEM_FAILED)
		ft_exit("Error semaphore fail\n");
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
		philos[i].died = &program->dead_flag;
		philos[i].forks = program->semaphore;
		i++;
	}
	init_program(program, philos, arg);
}
