/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:45:13 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/07 15:49:45 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating (t_philo *philo)
{
	philo->last_meal_time =  get_current_time_ms() - philo->start_time;
	ft_usleep(philo->time_to_eat);
	printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);
		printf("%ld %d has taken a fork\n", philo->last_meal_time, philo->philo_id);

	printf("%ld %d is eating\n", philo->last_meal_time, philo->philo_id);
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
}
