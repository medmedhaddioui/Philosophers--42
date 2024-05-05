/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/05 17:24:22 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_data *var)
{
    pthread_mutex_t mutexs[var->forks_nb];
    int i;
    i = 0;
    while (i < var->forks_nb)
	{
		pthread_mutex_init(&mutexs[i], NULL);
		i++;
	}
    return 0;
}
void init_philo (t_philo *philos, t_data *var)
{
    int i;
    i = 0;
  
    while (i < var->nb_of_philos)
    {
        philos[i].var.time_to_die = var->time_to_die;
        philos[i].var.time_to_eat = var->time_to_eat;
        philos[i].var.time_to_sleep = var->time_to_sleep;
        philos[i].var.nb_times_to_eat = var->nb_times_to_eat;
        philos[i].var.start_time = get_current_time_ms();
        philos[i].var.last_meal_time = get_current_time_ms();
        i++;
    }

}
int 	initialization(t_data *var, int ac, char **av)
{
	var->forks_nb = ft_atoi(av[1]);
	var->nb_of_philos = ft_atoi(av[1]);
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