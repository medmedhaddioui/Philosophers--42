/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:31:41 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/20 17:08:42 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(void)
{
	pid_t	id;
	int		i;
    id = 5;

	i = 0;
	while (i < 3)
	{
        id = fork();
		i++;
	}
}
