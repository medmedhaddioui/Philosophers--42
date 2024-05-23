/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:09:02 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/23 12:09:56 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_info(char *s, t_philo *philo)
{
    sem_wait(philo->write);
	philo->time = get_current_time_ms() - philo->start_time;
	printf("%ld %d %s", philo->time, philo->philo_id, s);
    sem_post(philo->write);
}
void eating(t_philo *philo)
{
	sem_wait(philo->forks);
	printf_info("has taken a fork\n",philo);
	sem_wait(philo->forks);
	printf_info("has taken a fork\n",philo);
	sem_wait(philo->meal_time);
	philo->last_meal = get_current_time_ms();
	philo->eating_count++;
	sem_post(philo->meal_time);
	printf_info("is eating\n", philo);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}
void thinking(t_philo *philo)
{
	printf_info("is sleeping\n", philo);
	ft_usleep(philo->time_to_sleep);
}
void sleeping(t_philo *philo)
{
	printf_info("is thinking\n", philo);
}