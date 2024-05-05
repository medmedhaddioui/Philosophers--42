/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:53 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/05 21:25:08 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine (void *data)
{
	t_philo *philo = data;
	printf("%d\n",philo->philo_id);
	return NULL;
}
void  thread_add(t_philo *philos, t_philo arg)
{
	int i;
	i = -1;
	while (++i < arg.nb_of_philos)
		pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]);
	i = 0;
	while (i < arg.nb_of_philos)
		pthread_join(philos[i++].thread, NULL);
}