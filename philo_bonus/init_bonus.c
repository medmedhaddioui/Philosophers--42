/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/23 20:27:51 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sem_create(t_program *prog, t_philo arg)
{
	sem_unlink("semaphore");
	sem_unlink("meal");
	sem_unlink("dead");
	sem_unlink("write");
	prog->semaphore = sem_open("semaphore", O_CREAT | O_EXCL , 0600, arg.nb_of_philos);
	if (prog->semaphore == SEM_FAILED)
		ft_exit("Error semaphore fail\n");
	prog->sem_meal = sem_open("meal", O_CREAT | O_EXCL , 0600, 1);
	if (prog->sem_meal == SEM_FAILED)
		ft_exit("Error semaphore fail\n");
	prog->sem_dead = sem_open("dead", O_CREAT | O_EXCL , 0600, 1);
	if (prog->sem_dead == SEM_FAILED)
		ft_exit("Error semaphore fail\n");
	prog->sem_write = sem_open("write", O_CREAT | O_EXCL , 0600, 1);
	if (prog->sem_write == SEM_FAILED)
		ft_exit("Error semaphore fail\n");
}

void	init_arg_philo(int i, t_philo *philos, t_philo arg, int ac)
{
	philos[i].philo_id = i + 1;
	philos[i].time_to_die = arg.time_to_die;
	philos[i].time_to_eat = arg.time_to_eat;
	philos[i].time_to_sleep = arg.time_to_sleep;
	philos[i].nb_of_philos = arg.nb_of_philos;
	if (ac == 6)
	{
		philos[i].nb_times_to_eat = arg.nb_times_to_eat;
		philos[i].flag = EAT_COUNT_ON;
	}
	else
		philos[i].flag = EAT_COUNT_OFF;
}

void	init_program(t_program *program, t_philo *philos, t_philo arg)
{
	program->pids = malloc(sizeof(pid_t) * arg.nb_of_philos);
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
		philos[i].time = 0;
		philos[i].last_meal = get_current_time_ms();
		philos[i].start_time = get_current_time_ms();
		philos[i].forks = program->semaphore;
		philos[i].dead = program->sem_dead;
		philos[i].write = program->sem_write;
		philos[i].meal_time = program->sem_meal;
		i++;
	}
	init_program(program, philos, arg);
}
