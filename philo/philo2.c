/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/01 17:11:16 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_arguments(int ac)
{
	if (ac != 5 && ac != 6)
		return (1);
	return (0);
}
void	initialization(int ac, char **av, t_data *var)
{
	var->nb_of_philos = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->nb_times_to_eat = ft_atoi(av[5]);
}

int thread_create(t_data *var)
{
    pthread_t *threads;
    threads = malloc (var->nb_of_philos);
    int i;
    while (i < var->nb_of_philos)
    {
        pthread_create(threads, NULL, func, NULL);
        i++;
    }
    i = 0;
    while (i < var->nb_of_philos)
    {
        pthread_join(threads,NULL);
    }
}