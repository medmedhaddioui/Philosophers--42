/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/10 20:53:59 by mel-hadd         ###   ########.fr       */
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
#define LOCK 1
#define UNLOCK 0

typedef struct s_philo
{  
    // philos data  //
    int philo_id;
    pthread_t thread;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    int  eating_count;
    size_t time;
    int nb_times_to_eat;
    int nb_of_philos;
  
    
    // forks //
    int fork_id ;
    pthread_mutex_t *mutexs;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    
    pthread_mutex_t *write_lock;
    pthread_mutex_t *meal_lock;
    pthread_mutex_t *dead_lock;

} t_philo;

typedef struct s_program
{
    int dead_flag;
    pthread_mutex_t write_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    t_philo *philos;
    
}   t_program;


int	check_arg(int argc, char **argv);
int 	check_arg_2(t_philo *arg, int ac, char **av);
int	ft_atoi(const char *nptr);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time_ms(void);
void init_philo (t_philo *philos, t_philo arg, t_program program);
int init_forks(t_philo *arg, t_program *program);
void  thread_add(t_philo *philos, t_philo arg, int ac);
void eating (t_philo *philo);
void sleeping (t_philo *philo);
void printf_info(char *s, t_philo * philo);
void locker(t_philo *philo, int flag);



#endif 