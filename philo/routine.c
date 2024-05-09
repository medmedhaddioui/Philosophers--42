/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:45:13 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/09 20:52:49 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
	pthread_mutex_lock(philo->second_fork);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
}
void unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}
void eating (t_philo *philo)
{
	philo->last_meal_time =  get_current_time_ms() - philo->start_time;
	lock_forks(philo);
	printf("%ld %d is eating\n", philo->last_meal_time, philo->philo_id);
		ft_usleep(philo->time_to_eat);
	philo->nb_times_to_eat--;
	unlock_forks(philo);
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
	printf("%ld %d is sleeping\n", philo->last_meal_time, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}
