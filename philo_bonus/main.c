/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:52:32 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/25 12:52:54 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg_2(t_philo *arg, int ac, char **av)
{
	arg->nb_of_philos = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->nb_times_to_eat = ft_atoi(av[5]);
	if (arg->nb_of_philos <= 0 || arg->time_to_die <= 0
		|| arg->nb_of_philos > PHILO_LIMTS || arg->time_to_eat <= 0
		|| arg->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philos[PHILO_LIMTS];
	t_philo		arg;
	t_program	program;

	if (check_arg(ac, av))
		return (write(2, "Invalid arguments\n", 19), 1);
	if (check_arg_2(&arg, ac, av))
		return (write(2, "Invalid arguments\n", 19), 1);
	sem_create(&program, arg);
	init_philo(philos, arg, &program, ac);
	simulation_philos(philos, &program);
	return (0);
}
