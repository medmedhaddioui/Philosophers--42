/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/15 12:22:13 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine (void *data)
{
	t_philo *philo = data;
	
	while (!dead_lock_func(philo))
	{
		if (philo->flag == EAT_COUNT_ON && philo->nb_times_to_eat == philo->eating_count)
		{
			pthread_mutex_lock(philo->full_lock);
			philo->full = FULL;
			pthread_mutex_unlock(philo->full_lock);
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
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", philo->time, philo->philo_id);
	printf("%ld %d is Dead\n" , philo->time_to_die, philo->philo_id);
	pthread_mutex_unlock(philo->l_fork);
}

int check_philos_full (t_program * prog)
{
	int i = 0;
	while (i < prog->nb_philos)
	{ 
		if (check_full(prog, i) == 0)
			return 0;
		i++;
	}
	return 1;
}
int  check_full(t_program *prog, int i)
{
	pthread_mutex_lock(prog->philos[i].full_lock);
	if (prog->philos[i].full == FULL)
		return (pthread_mutex_unlock(prog->philos[i].full_lock), 1);
	pthread_mutex_unlock(prog->philos[i].full_lock);
	return 0;
}
void *ft_check_death (void *data)
{
	t_program *prog = data;
	int i = 0;
	size_t time_check;
	size_t time_die = prog->philos[0].time_to_die;
	pthread_mutex_lock(prog->philos[0].meal_lock);
	time_check = get_current_time_ms() - prog->philos[i].last_meal;
	pthread_mutex_unlock(prog->philos[0].meal_lock);
	while (time_check <= time_die || check_full (prog, i) == 1)
	{		
		if (check_full(prog, i))
		{
			if(check_philos_full(prog) == 1)
				return NULL;
		}
		if (prog->nb_philos == i + 1)
			i = -1;
		i++;
		pthread_mutex_lock(prog->philos[i].meal_lock);
		time_check = get_current_time_ms() - prog->philos[i].last_meal;
		pthread_mutex_unlock(prog->philos[i].meal_lock);
	}
	pthread_mutex_lock(prog->philos[0].dead_lock);
	prog->dead_flag = 1;
	pthread_mutex_unlock(prog->philos[0].dead_lock);
	printf("%ld %d is Dead\n" ,time_die, prog->philos[i].philo_id);
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
		return (destroy_all(&philos[0]),one_philo(&philos[i]));
	if (pthread_create(&check_death, NULL, &ft_check_death, (void *)program))
		return(destroy_all(&philos[0]));
	while (i < arg.nb_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]))
			return(destroy_all(&philos[0]));
		usleep(200);
		i++;
	}
	if (pthread_join(check_death, NULL))
		return (destroy_all(&philos[0]));
	i = 0;
	while (i < arg.nb_of_philos)
	{
		if (pthread_join(philos[i++].thread, NULL))
			return (destroy_all(&philos[0]));
	}
	destroy_all(&philos[0]);
}