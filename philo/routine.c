/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:45:13 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/09 16:38:41 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating (t_philo *philo)
{
	philo->last_meal_time =  get_current_time_ms() - philo->start_time;
	// pthread_mutex_lock(&philo->write_lock);
	pthread_mutex_lock(philo->first_fork);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
	pthread_mutex_lock(philo->second_fork);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
	ft_usleep(philo->time_to_eat);
	
	printf("%ld %d is eating\n", philo->last_meal_time, philo->philo_id);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void thinking (t_philo *philo)
{
	philo->last_meal_time =  get_current_time_ms() - philo->start_time;
	ft_usleep(philo->time_to_eat);
	printf("%ld %d is thinking\n", philo->last_meal_time, philo->philo_id);
}

void sleeping (t_philo *philo)
{
	philo->last_meal_time =  get_current_time_ms() -philo->start_time ;
	ft_usleep(philo->time_to_sleep);
	printf("%ld %d is sleeping\n", philo->last_meal_time, philo->philo_id);
	// thread_mutex_unlock(&philo->write_lock);
}
