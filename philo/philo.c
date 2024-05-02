/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:26:11 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/05/01 17:03:43 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
    t_data var;
    if (check_arguments(ac))
        return 1;
    initialization(ac, av, &var);
    thread_create(&var);
    return 0;
}