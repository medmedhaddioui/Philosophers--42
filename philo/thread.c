/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/18 12:38:51 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!dead_lock_func(philo))
	{
		if (philo->flag == EAT_COUNT_ON
			&& philo->nb_times_to_eat == philo->eating_count)
		{
			pthread_mutex_lock(philo->full_lock);
			philo->full = FULL;
			pthread_mutex_unlock(philo->full_lock);
			break ;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", philo->time, philo->philo_id);
	printf("%ld %d is Dead\n", philo->time_to_die, philo->philo_id);
	pthread_mutex_unlock(philo->l_fork);
}

int	check_other_philos_full(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		if (check_full_lock(prog, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	*ft_check_death(void *data)
{
	t_program	*prog;
	int			i;
	size_t		time_die;

	prog = data;
	i = 0;
	time_die = prog->philos[0].time_to_die;
	while (time_check_lock(prog, i) <= time_die || check_full_lock(prog,
			i) == 1)
	{
		if (check_full_lock(prog, i))
		{
			if (check_other_philos_full(prog) == 1)
				return (NULL);
		}
		if (prog->nb_philos == i + 1)
			i = -1;
		i++;
	}
	pthread_mutex_lock(prog->philos[0].dead_lock);
	prog->dead_flag = 1;
	pthread_mutex_unlock(prog->philos[0].dead_lock);
	printf("%ld %d is Dead\n", time_die, prog->philos[i].philo_id);
	return (NULL);
}

void	thread_add(t_philo *philos, t_philo arg, t_program *program)
{
	int			i;
	pthread_t	check_death;

	i = 0;
	if (arg.nb_of_philos == 1)
		return (one_philo(&philos[i]), destroy_all(&philos[0]));
	if (pthread_create(&check_death, NULL, &ft_check_death, (void *)program))
		return (destroy_all(&philos[0]));
	while (i < arg.nb_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine,
				(void *)&philos[i]))
			return (destroy_all(&philos[0]));
		i++;
	}
	if (pthread_join(check_death, NULL))
		return (destroy_all(&philos[0]));
	i = 0;
	while (i < arg.nb_of_philos)
	{
		if (pthread_join(philos[i++].thread, NULL))
			return (destroy_all(&philos[0]));
	}
	destroy_all(&philos[0]);
}
