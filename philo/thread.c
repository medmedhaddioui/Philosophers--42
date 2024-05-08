/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/07 19:22:27 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine (void *data)
{
	t_philo *philo = data;
	while (1)
	{
		if (philo->philo_id % 2 == 0)
			thinking(philo);
		pthread_mutex_lock(philo->first_fork);
		pthread_mutex_lock(philo->second_fork);
			eating(philo);
			sleeping(philo);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
	}

	return NULL;
}

void  thread_add(t_philo *philos, t_philo arg)
{
	
	int i;
	i = -1;
	if (philos->nb_times_to_eat == 0)
		return 1;
	
	while (++i < arg.nb_of_philos)
		pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]);
	i = 0;
	while (i < arg.nb_of_philos)
		pthread_join(philos[i++].thread, NULL);
}