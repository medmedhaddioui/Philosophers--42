/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/04 13:17:36 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
#include <stdlib.h>
#define PHILO_LIMTS 200

typedef struct s_data
{
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    int nb_times_to_eat;
    int nb_of_philos;
    int forks_nb;

} t_data;

typedef struct s_philo
{
    pthread_t threads;
} t_philo ;

int check_arguments(int argc, char **argv);
int 	initialization(t_data *var, int ac, char **av);
int init_philo(t_data *var , int ac, char **av);
int	ft_atoi(const char *nptr);
void init_forks(t_data *var);

#endif 