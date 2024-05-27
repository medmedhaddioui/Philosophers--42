/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:21:48 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/26 22:11:33 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void ft_error (char *s, t_philo *philo)
{
	perror(s);
	sem_cleanup(philo,ON);
	exit(EXIT_FAILURE);
}
void	sem_cleanup(t_philo *philo, int flag)
{
	if (sem_close(philo->forks) == -1)
		ft_exit("Error closing semaphore");
	if (sem_close(philo->meal_time) == -1)
		ft_exit("Error closing semaphore");
	if (sem_close(philo->dead) == -1)
		ft_exit("Error closing semaphore");
	if (sem_close(philo->write) == -1)
		ft_exit("Error closing semaphore");
	if (flag == ON)
		free(philo->pids2);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

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

size_t	get_current_time_ms(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time_ms();
	while (get_current_time_ms() - start < milliseconds)
		usleep(100);
	return (0);
}
