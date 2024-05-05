/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/05 21:24:55 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#define PHILO_LIMTS 200

typedef struct s_data
{
    
    // bool full;

} t_data;


typedef struct s_philo
{
    pthread_t thread;
    int philo_id;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    size_t last_meal_time;
    int nb_times_to_eat;
    int nb_of_philos;
    
} t_philo;



int	check_arg(int argc, char **argv);
int 	check_arg_2(t_philo *arg, int ac, char **av);
int	ft_atoi(const char *nptr);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time_ms(void);
void init_philo (t_philo *philos, t_philo arg);
int init_forks(t_philo arg);
void  thread_add(t_philo *philos, t_philo arg);



#endif 