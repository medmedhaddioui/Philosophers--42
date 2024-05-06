/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/06 17:49:25 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void eating (t_philo *philo)
{
	philo->start_time = get_current_time_ms();
	ft_usleep(philo->time_to_eat);
	philo->last_meal_time =  get_current_time_ms() -philo->start_time ;
	printf("%ld %d is eating\n", philo->last_meal_time, philo->philo_id);
}

void thinking (t_philo *philo)
{
	printf("%ld %d is thinking\n", philo->start_time, philo->philo_id);
}

void sleeping (t_philo *philo)
{
	ft_usleep(philo->time_to_sleep);
	printf("%ld %d is sleeping\n", philo->start_time, philo->philo_id);
}
void *routine (void *data)
{
	t_philo *philo = data;

	if (philo->philo_id % 2 == 0)
	{
		eating (philo);
		thinking(philo);
		sleeping(philo);
	}
	return NULL;
}

void  thread_add(t_philo *philos, t_philo arg)
{
	int i;
	i = -1;
	while (++i < arg.nb_of_philos)
		pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]);
	i = 0;
	while (i < arg.nb_of_philos)
		pthread_join(philos[i++].thread, NULL);
}