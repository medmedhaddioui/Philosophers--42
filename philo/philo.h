/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/15 12:01:56 by mel-hadd         ###   ########.fr       */
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
#define EAT_COUNT_ON 1
#define EAT_COUNT_OFF 0
#define FULL 2

typedef struct s_philo
{  
    // philos data  //
    pthread_t thread;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    size_t last_meal;
    size_t time;
    int philo_id;
    int eating_count;
    int nb_times_to_eat;
    int nb_of_philos;
    int *died;
    int flag;
    int full;
    
    // forks //
    int fork_id ;
    pthread_mutex_t *mutexs;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    
    // for data race
    pthread_mutex_t *write_lock;
    pthread_mutex_t *meal_lock;
    pthread_mutex_t *dead_lock;

} t_philo;

typedef struct s_program
{
    int dead_flag;
    int nb_philos;
    pthread_mutex_t write_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    t_philo *philos;
    
}   t_program;


int	check_arg(int argc, char **argv);
int 	check_arg_2(t_philo *arg, int ac, char **av);
int	ft_atoi(const char *nptr);
int	ft_usleep(t_philo *philo, size_t milliseconds);
size_t	get_current_time_ms(void);
void init_philo (t_philo *philos, t_philo arg, t_program *program, int ac);
int init_forks(t_philo *arg, t_program *program);
void eating (t_philo *philo);
void  thread_add(t_philo *philos, t_philo arg, t_program *program ,int ac);
void sleeping (t_philo *philo);
void printf_info(char *s, t_philo * philo);
void locker(t_philo *philo, int flag);
void thinking (t_philo *philo);
void destroy_all (t_philo *philo);


#endif 