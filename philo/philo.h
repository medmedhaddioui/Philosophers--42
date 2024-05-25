/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/25 12:42:02 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# define PHILO_LIMTS 200
# define LOCK 1
# define UNLOCK 0
# define EAT_COUNT_ON 1
# define EAT_COUNT_OFF -1
# define FULL 2

typedef struct s_philo
{
	// philos data  //
	pthread_t		thread;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_meal;
	size_t			time;
	int				philo_id;
	int				eating_count;
	int				nb_times_to_eat;
	int				nb_of_philos;
	int				*died;
	int				flag;
	int				full;

	// forks //
	int				fork_id;
	pthread_mutex_t	mutexs[200];
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	// locks
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*full_lock;

}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	int				nb_philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	full_lock;
	t_philo			*philos;

}					t_program;

int					check_arg(int argc, char **argv);
int					check_arg_2(t_philo *arg, int ac, char **av);
int					ft_atoi(const char *nptr);
int					ft_usleep(t_philo *philo, size_t milliseconds);
size_t				get_current_time_ms(void);
void				init_philo(t_philo *philos, t_philo arg, t_program *program,
						int ac);
int					init_forks(t_philo *arg, t_program *program);
void				eating(t_philo *philo);
void				thread_add(t_philo *philos, t_philo arg,
						t_program *program);
void				sleeping(t_philo *philo);
void				printf_info(char *s, t_philo *philo);
void				destroy_all(t_philo *philo, t_philo arg);
int					dead_lock_func(t_philo *philo);
int					check_full_lock(t_program *prog, int i);
void				even_lock(t_philo *philo, int flag);
void				odd_lock(t_philo *philo, int flag);
size_t				time_check_lock(t_program *prog, int i);
void				thinking(t_philo *philo);

#endif
