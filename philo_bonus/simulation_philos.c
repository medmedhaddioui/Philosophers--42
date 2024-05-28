/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/28 14:16:36 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_time(t_philo *philo, size_t time_now)
{
	if (time_now > philo->time_to_die)
	{
		sem_wait(philo->write);
		printf("%ld %d is dead\n", time_now, philo->philo_id);
		sem_post(philo->dead);
		sem_wait(philo->sem_flag);
		philo->dead_flag = 1;
		sem_post(philo->sem_flag);
		return (1);
	}
	else
		return (0);
}

void	*ft_check_death(void *data)
{
	t_philo	*philo;
	size_t	time_now;
	int		eating_done;

	philo = data;
	while (1)
	{
		sem_wait(philo->dead);
		sem_wait(philo->meal_time);
		time_now = get_current_time_ms() - philo->last_meal;
		eating_done = philo->eating_count;
		sem_post(philo->meal_time);
		if (check_time(philo, time_now))
			return (NULL);
		if (philo->flag == EAT_COUNT_ON)
		{
			if (eating_done == philo->nb_times_to_eat)
				return (sem_post(philo->dead), NULL);
		}
		sem_post(philo->dead);
		usleep(300);
	}
	return (NULL);
}

void	philo_checker(t_philo *philo, pthread_t check_death, int i)
{
	int	check;

	if (i == DIE_CHECK)
	{
		sem_wait(philo->sem_flag);
		check = philo->dead_flag;
		sem_post(philo->sem_flag);
		if (check == 1)
		{
			pthread_join(check_death, NULL);
			sem_cleanup(philo);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (philo->flag == EAT_COUNT_ON
			&& philo->nb_times_to_eat == philo->eating_count)
		{
			pthread_join(check_death, NULL);
			sem_cleanup(philo);
			exit(EXIT_SUCCESS);
		}
	}
}

void	routine(t_philo *philo)
{
	pthread_t	check_death;

	if (pthread_create(&check_death, NULL, &ft_check_death, (void *)philo) != 0)
		ft_error("Error pthread_create\n", philo);
	while (1)
	{
		philo_checker(philo, check_death, EAT_CHECK);
		philo_checker(philo, check_death, DIE_CHECK);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	if (pthread_join(check_death, NULL) != 0)
		ft_error("Error pthread_join\n", philo);
}

void	simulation_philos(t_philo *philos, t_program *prog)
{
	int		i;
	int		status;
	pid_t	pids[PHILO_LIMTS];

	i = 0;
	while (i < prog->nb_philos)
	{
		prog->id = fork();
		if (prog->id < 0)
			ft_exit("Error fork\n");
		if (prog->id == 0)
			routine(&philos[i]);
		pids[i] = prog->id;
		i++;
	}
	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < prog->nb_philos)
				kill(pids[i++], SIGKILL);
		}
	}
	sem_cleanup(&philos[0]);
}
