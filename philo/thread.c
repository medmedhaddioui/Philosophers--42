/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/05 17:21:56 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void * routine (void *data)
{
	t_philo *philo = data;
	printf("%zu\n",philo->var.time_to_die);
	return NULL;
}
void  thread_add(t_philo *philos, char **av, t_data *var)
{
	(void) av;
	int i;
	i = 0;
	while (i < var->nb_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i].var);
		i++;
	}
	i = 0;
	while (i < var->nb_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}