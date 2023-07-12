/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:20:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/11 00:23:02 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int    read_input(t_vars *vars, char **av)
{
	vars->j = 0;
	vars->nb_of_eat = -1;
    while (av[++vars->j])
	{
		vars->i = -1;
		while (av[vars->j][++vars->i])
		{
			if (!ft_isdigit(av[vars->j][vars->i]))
				return (0);
		}
		if(vars->j == 1)
			vars->nb_of_philo = ft_atoi(av[1]);
		else if (vars->j == 2)
			vars->time_to_die = ft_atoi(av[2]);
		else if (vars->j == 3)
			vars->time_to_eat = ft_atoi(av[3]);
		else if (vars->j == 4)
			vars->time_to_sleep = ft_atoi(av[4]);
		else if (vars->j == 5)
			vars->nb_of_eat = ft_atoi(av[5]);
	}
	return (init_data(vars));
}

int	init_data(t_vars *vars)
{
	if (vars->nb_of_philo == 0)
		return (0);
	if (!(vars->philos = malloc(sizeof(t_philo) * vars->nb_of_philo)))
		return (free(vars->philos), 0);
		
	if (!(vars->fork_mutex = malloc(sizeof(pthread_mutex_t) * vars->nb_of_philo)))
		return (free(vars->fork_mutex), free(vars->philos), 0);
	vars->x = 0;
	while (vars->x < vars->nb_of_philo)
	{
		vars->philos[vars->x].id = vars->x + 1;
    	vars->philos[vars->x].start_date = c_time();
    	vars->philos[vars->x].last_eat = c_time();
    	vars->philos[vars->x].nb_eat = 0;
		vars->x++;
	}
	return (1);
}