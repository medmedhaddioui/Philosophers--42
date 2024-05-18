/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:45:13 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/18 12:39:12 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_info(char *s, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (!dead_lock_func(philo))
	{
		philo->time = get_current_time_ms() - philo->start_time;
		printf("%ld %d %s", philo->time, philo->philo_id, s);
	}
	pthread_mutex_unlock(philo->write_lock);
}

void	eating(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		odd_lock(philo, LOCK);
	else
		even_lock(philo, LOCK);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->full_lock);
	philo->eating_count++;
	pthread_mutex_unlock(philo->full_lock);
	printf_info("is eating\n", philo);
	ft_usleep(philo, philo->time_to_eat);
	if (philo->philo_id % 2 != 0)
		odd_lock(philo, UNLOCK);
	else
		even_lock(philo, UNLOCK);
}

void	sleeping(t_philo *philo)
{
	printf_info("is sleeping\n", philo);
	ft_usleep(philo, philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	printf_info("is thinking\n", philo);
}
