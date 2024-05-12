/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:45:13 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/11 15:26:47 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printf_info(char *s, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (philo->died != 1)
	{
		philo->time = get_current_time_ms() - philo->start_time;
		printf("%ld %d %s",philo->time, philo->philo_id,s);
	}
	pthread_mutex_unlock(philo->write_lock);
}

void locker(t_philo *philo, int flag)
{
	if (flag == LOCK)
	{
		pthread_mutex_lock(philo->first_fork);
		printf_info("has taken a fork\n", philo);
		pthread_mutex_lock(philo->second_fork);
		printf_info("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
	}
}

void eating (t_philo *philo)
{
	philo->last_meal = get_current_time_ms();
	locker(philo, LOCK);
	pthread_mutex_lock(philo->meal_lock);
	printf_info("is eating\n",philo);
	philo->eating_count++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	if ((get_current_time_ms()) - philo->last_meal > philo->time_to_die)
		philo->died = 1;
	locker(philo, UNLOCK);
}

void sleeping (t_philo *philo)
{
	printf_info("is sleeping\n",philo);
	ft_usleep(philo->time_to_sleep);
	if (get_current_time_ms() - philo->last_meal > philo->time_to_die)
		philo->died = 1;
}
