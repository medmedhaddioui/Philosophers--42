/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/04 13:16:51 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *routine ()
{
	printf("Successss\n");
	return NULL;
}
int init_philo(t_data *var , int ac, char **av)
{
	(void ) ac;
	(void) av;
	int i;
	i  = 0;
	t_philo philos[var->nb_of_philos];
	while (i < var->nb_of_philos)
	{
		if (pthread_create(&philos[i].threads, NULL, &routine, NULL))
			return 1;
		i++;
	}
	i = 0;
	while (i < var->nb_of_philos)
	{
		if (pthread_join(philos[i].threads, NULL))
			return 1;
		i++;
	}
	return 0;
}
void init_forks(t_data *var)
{
	int i = 0;
	pthread_mutex_t mutexs[var->forks_nb];
	while (i < var->forks_nb)
	{
		pthread_mutex_init(&mutexs[i], NULL);
		i++;
	}
}
int 	initialization(t_data *var, int ac, char **av)
{
	var->nb_of_philos = ft_atoi(av[1]);
	var->forks_nb = ft_atoi(av[1]);
    if (var->nb_of_philos <= 0)
        return (write(2, "Invalid arguments of philos\n", 29), 1);
    var->time_to_die = ft_atoi(av[2]);
    if (var->time_to_die <= 0)
        return (write(2, "Invalid time_to_die\n", 21), 1);
    var->time_to_eat = ft_atoi(av[3]);
    if (var->time_to_eat <= 0)
        return (write(2, "Invalid time_to_eat\n", 21), 1);
    var->time_to_sleep = ft_atoi(av[4]);
    if (var->time_to_sleep <= 0)
        return (write(2, "Invalid time_to_sleep\n", 23), 1);
    if (ac == 6)
        var->nb_times_to_eat = ft_atoi(av[5]);
    if (var->nb_of_philos > PHILO_LIMTS)
        return 1;
    return 0;
}