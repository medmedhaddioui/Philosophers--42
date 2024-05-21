/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:09:02 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/21 17:15:48 by mel-hadd         ###   ########.fr       */
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
	if (sem_wait(prog->semaphore) == -1)
		ft_exit("Error sem_wait fail\n");
	printf_info("has taken a fork\n",philo);
	// sem_wait(philo->r_fork);
	// printf_info("has taken a fork\n",philo);
	printf_info("is eating\n", philo);
	ft_usleep(philo->time_to_eat);
	// sem_post(philo->r_fork);
	if (sem_post(prog->semaphore))
		ft_exit("Error sem_post fail\n");
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