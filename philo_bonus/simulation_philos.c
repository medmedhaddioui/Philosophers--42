/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:29:43 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/22 15:31:00 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*ft_check_death(void *data)
{
    int i;
    i = 0;
    t_program *prog = data;
    size_t time;
    sem_wait(prog->meal_eat);
    time = get_current_time_ms() - prog->philos[i].last_meal;
    sem_post(prog->meal_eat);
    while (time <= prog->philos[0].time_to_die)
    {
        if (prog->nb_philos == i + 1)
			i = -1;
		i++;
        sem_wait(prog->meal_eat);
        time = get_current_time_ms() - prog->philos[i].last_meal;
        sem_post(prog->meal_eat);

    }
    if (time > prog->philos[i].time_to_die)
    {
        printf("Dead\n");
        sem_wait(prog->dead);
        exit(EXIT_FAILURE);
    }
    return NULL;
}
void routine (t_philo *philo, t_program *prog)
{
    // pthread_t check_death;
    // pthread_create(&check_death, NULL, &ft_check_death, (void *) philo);
    if (philo->philo_id % 2 != 0)
        ft_usleep(1);
    while (1)
    {
        if (philo->flag == EAT_COUNT_ON && philo->nb_times_to_eat == philo->eating_count)
            exit(EXIT_SUCCESS);
        eating(philo, prog);
        sleeping(philo);
        thinking(philo);
    }
}

void simulation_philos (t_philo *philos, t_program *prog)
{
    int i;
    i = 0;
    pid_t id;
    while (i < prog->nb_philos)
    {
        id = fork();
        if (id == 0)
        {
            routine(&philos[i], prog);
            sem_cleanup(prog);
        }
        i++;
    }
    i = 0;
    while (i < prog->nb_philos)
    {
        wait(NULL);
        i++;
    }
}