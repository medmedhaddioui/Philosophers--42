/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/26 22:11:17 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_death(void *data)
{
	t_philo	*philo;
	size_t	time_now;

	philo = data;
	while (1)
	{
		sem_wait(philo->dead);
		sem_wait(philo->meal_time);
		time_now = get_current_time_ms() - philo->last_meal;
		sem_post(philo->meal_time);
		if (time_now > philo->time_to_die)
		{
			sem_wait(philo->write);
			printf("%ld %d is dead\n", philo->time, philo->philo_id);
			sem_cleanup(philo,ON);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->dead);
		usleep(500);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_t	check_death;

	if (pthread_create(&check_death, NULL, &ft_check_death, (void *)philo) != 0)
		ft_error("Error pthread_create\n",philo);
	while (1)
	{
		if (philo->flag == EAT_COUNT_ON
			&& philo->nb_times_to_eat == philo->eating_count)
			{	
				sem_cleanup(philo,ON);
				exit(EXIT_SUCCESS);
			}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	if (pthread_join(check_death,NULL) != 0)
		ft_error("Error pthread_join\n",philo);
}

void	simulation_philos(t_philo *philos, t_program *prog)
{
	int	i;
	int	status;

	i = 0;
	while (i < prog->nb_philos)
	{
		prog->id = fork();
		if (prog->id < 0)
			ft_exit("Error fork\n");
		if (prog->id == 0)
			routine(&philos[i]);
		prog->pids[i] = prog->id;
		i++;
	}
	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < prog->nb_philos)
				kill(prog->pids[i++], SIGKILL);
		}
	}
	sem_cleanup(&philos[0], OFF);
	free(prog->pids);
}
