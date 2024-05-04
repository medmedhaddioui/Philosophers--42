/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:26:11 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/04 13:16:40 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, char **argv)
{
	int i;
	i = 1;
	int j ;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while(argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return 1;
		}
		i++;
	}
	return (0);

}

int main (int ac, char **av)
{
    t_data var;
    if (check_arguments(ac ,av))
        return (write(2,"Invalid arguments\n",19), 1);
    if (initialization(&var, ac, av))
        return 1;
    init_forks(&var);
    if (init_philo(&var,ac,av))
        return 1;
    return 0;
}