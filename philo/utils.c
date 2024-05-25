/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:36:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/25 12:51:34 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (0);
		nptr++;
	}
	return (sign * result);
}

void	destroy_all(t_philo *philo, t_philo arg)
{
	int	i;

	i = 0;
	while (i < arg.nb_of_philos)
	{
		pthread_mutex_destroy(&arg.mutexs[i]);
		i++;
	}
	pthread_mutex_destroy(philo->meal_lock);
	pthread_mutex_destroy(philo->write_lock);
	pthread_mutex_destroy(philo->dead_lock);
	pthread_mutex_destroy(philo->full_lock);
	return ;
}

size_t	get_current_time_ms(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time_ms();
	while (!dead_lock_func(philo) && (get_current_time_ms()
			- start) < milliseconds)
		usleep(100);
	return (0);
}
