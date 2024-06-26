/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:18 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/28 14:15:45 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PHILO_LIMTS 200
# define LOCK 1
# define UNLOCK 0
# define EAT_COUNT_ON 1
# define EAT_COUNT_OFF -1
# define FULL 2
# define ON 1
# define OFF 0
# define EAT_CHECK 0
# define DIE_CHECK 1

typedef struct s_philo
{
	// philos data  //
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	last_meal;
	size_t	start_time;
	size_t	time;
	int		philo_id;
	int		eating_count;
	int		nb_times_to_eat;
	int		nb_of_philos;
	int		flag;
	sem_t	*forks;
	sem_t	*dead;
	sem_t	*write;
	sem_t	*meal_time;
	sem_t	*sem_flag;
	int		dead_flag;
}			t_philo;

typedef struct s_program
{
	pid_t	id;
	sem_t	*semaphore;
	sem_t	*sem_meal;
	sem_t	*sem_dead;
	sem_t	*sem_write;
	sem_t	*sem_flag;
	int		nb_philos;
	t_philo	*philos;

}			t_program;

int			check_arg(int argc, char **argv);
int			check_arg_2(t_philo *arg, int ac, char **av);
int			ft_atoi(const char *nptr);
size_t		get_current_time_ms(void);
void		init_philo(t_philo *philos, t_philo arg, t_program *program,
				int ac);

void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		printf_info(char *s, t_philo *philo);
void		ft_exit(char *s);
void		sem_create(t_program *prog, t_philo arg);
void		simulation_philos(t_philo *philos, t_program *prog);
void		sem_cleanup(t_philo *philo);
int			ft_usleep(size_t milliseconds);
void		ft_error(char *s, t_philo *philo);

#endif
