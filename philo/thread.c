/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/09 16:39:09 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine (void *data)
{
	t_philo *philo = data;
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->time_to_eat + 1);
	while (!philo->dead)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}
void one_philo (t_philo * philo)
{
	pthread_mutex_lock(philo->first_fork);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
		printf("%ld %d is Dead" , philo->last_meal_time, philo->philo_id);
	pthread_mutex_unlock(philo->first_fork);
}
void  thread_add(t_philo *philos, t_philo arg)
{
	
	int i;
	i = 0;
	if (arg.nb_times_to_eat == 0)
		return ; 
	if (arg.nb_of_philos == 1)
		return (one_philo(&philos[i]));
	while (i < arg.nb_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < arg.nb_of_philos)
		if (pthread_join(philos[i++].thread, NULL))
			return ;
}