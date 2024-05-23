/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:09:02 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/22 15:27:56 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_info(char *s, t_philo *philo)
{
	philo->time = get_current_time_ms() - philo->start_time;
	printf("%ld %d %s", philo->time, philo->philo_id, s);
}
void eating(t_philo *philo, t_program *prog)
{
	sem_wait(philo->forks);
	printf_info("has taken a fork\n",philo);
	sem_wait(philo->forks);
	printf_info("has taken a fork\n",philo);
	sem_wait(prog->meal_eat);
	philo->last_meal = get_current_time_ms();
	philo->eating_count++;
	sem_post(prog->meal_eat);
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