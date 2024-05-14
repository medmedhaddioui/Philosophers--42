/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/14 14:26:19 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine (void *data)
{
	t_philo *philo = data;
	if (philo->philo_id % 2 != 0)
		ft_usleep(1);
	while (philo->died != 1)
	{
		if (philo->flag == EAT_COUNT_ON && philo->nb_times_to_eat == philo->eating_count)
		{
			philo->full = FULL;
			break;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}

void one_philo (t_philo * philo)
{
	pthread_mutex_lock(philo->first_fork);
	printf("%ld %d has taken a fork\n", philo->time, philo->philo_id);
	printf("%ld %d is Dead\n" , philo->time_to_die, philo->philo_id);
	pthread_mutex_unlock(philo->first_fork);
}

int check_philos_full (t_program * program)
{
	int i = 0;
	while (i < program->nb_philos)
	{ 
		if (program->philos[i].full != FULL)
			return 0;
		i++;
	}
	return 1;
}
void *ft_check_death (void *data)
{
	t_program *program = data;
	size_t time_die = program->philos[0].time_to_die;
	int i = 0;
	int j;
	while (get_current_time_ms() - program->philos[i].last_meal <= time_die)
	{
		if (program->philos[i].full == FULL)
		{
			if(check_philos_full(program))
				return NULL;
		}
		if (program->nb_philos == i + 1)
			i = 0;
		i++;
	}
	j = 0;
	while (j < program->nb_philos)
		program->philos[j++].died  = 1;
	printf("%ld %d is Dead\n" ,time_die, program->philos[i].philo_id);
	return NULL;
}

void  thread_add(t_philo *philos, t_philo arg, t_program *program ,int ac)
{
	int i;
	i = 0;
	pthread_t check_death ;

	if (ac == 6 && arg.nb_times_to_eat == 0)
		return ; 
	if (arg.nb_of_philos == 1)
		return (one_philo(&philos[i]));
	if (pthread_create(&check_death, NULL, &ft_check_death, (void *)program))
		return ;
	while (i < arg.nb_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]))
			return ;
		i++;
	}
	if (pthread_join(check_death, NULL))
			return ;
	i = 0;
	while (i < arg.nb_of_philos)
		if (pthread_join(philos[i++].thread, NULL))
			return ;
}