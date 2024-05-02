/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/01 17:03:19 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    int nb_times_to_eat;
    int nb_of_philos;

} t_data;

int check_arguments(int ac);
void initialization(int ac, char **av, t_data *var);

#endif 