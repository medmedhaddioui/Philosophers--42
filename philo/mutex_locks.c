/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_locks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:01:56 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/18 12:37:15 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full_lock(t_program *prog, int i)
{
	pthread_mutex_lock(prog->philos[i].full_lock);
	if (prog->philos[i].full == FULL)
		return (pthread_mutex_unlock(prog->philos[i].full_lock), 1);
	pthread_mutex_unlock(prog->philos[i].full_lock);
	return (0);
}

size_t	time_check_lock(t_program *prog, int i)
{
	size_t	time;

	pthread_mutex_lock(prog->philos[0].meal_lock);
	time = get_current_time_ms() - prog->philos[i].last_meal;
	pthread_mutex_unlock(prog->philos[0].meal_lock);
	return (time);
}

int	dead_lock_func(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->died == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	odd_lock(t_philo *philo, int flag)
{
	if (flag == LOCK)
	{
		usleep(500);
		pthread_mutex_lock(philo->l_fork);
		printf_info("has taken a fork\n", philo);
		pthread_mutex_lock(philo->r_fork);
		printf_info("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	even_lock(t_philo *philo, int flag)
{
	if (flag == LOCK)
	{
		pthread_mutex_lock(philo->r_fork);
		printf_info("has taken a fork\n", philo);
		pthread_mutex_lock(philo->l_fork);
		printf_info("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
