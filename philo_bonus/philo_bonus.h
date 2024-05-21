/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/20 15:47:19 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>

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

}					t_philo;

typedef struct s_program
{
	pid_t id;
	int				dead_flag;
	int				nb_philos;
	t_philo			*philos;

}					t_program;

int					check_arg(int argc, char **argv);
int					check_arg_2(t_philo *arg, int ac, char **av);
int					ft_atoi(const char *nptr);
int					ft_usleep(t_philo *philo, size_t milliseconds);
size_t				get_current_time_ms(void);
void				init_philo(t_philo *philos, t_philo arg, t_program *program,
						int ac);

#endif