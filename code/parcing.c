/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:20:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/17 06:46:38 by ebelfkih         ###   ########.fr       */
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
	vars->x = -1;
	while (++vars->x < vars->nb_of_philo)
		pthread_mutex_init(&vars->fork_mutex[vars->x], NULL);
	pthread_mutex_init(&vars->mutex, NULL);
	pthread_mutex_init(&vars->print, NULL);
	vars->x = 0;
	while (vars->x < vars->nb_of_philo)
	{
		vars->philos[vars->x].data = vars;
		vars->philos[vars->x].id = vars->x + 1;
    	vars->philos[vars->x].nb_eat = 0;
		// printf("numbers meals %p\n", &vars->philos[vars->x].nb_eat);
		// printf("last eat %p\n", &vars->philos[vars->x].last_eat);

		vars->philos[vars->x].state = 0;
    	vars->philos[vars->x].last_eat = c_time();
		vars->x++;
	}
	vars->start_time = c_time();
	return (1);
}

void mu_lock(int lu, int id, t_vars *vars)
{
	if (lu == 1)
	{
		pthread_mutex_lock(&vars->fork_mutex[id - 1]);
		if (id == vars->nb_of_philo)
			pthread_mutex_lock(&vars->fork_mutex[0]);
		else
			pthread_mutex_lock(&vars->fork_mutex[id]);
	}
	else
	{
		pthread_mutex_unlock(&vars->fork_mutex[id - 1]);
		if (id == vars->nb_of_philo)
			pthread_mutex_unlock(&vars->fork_mutex[0]);
		else
			pthread_mutex_unlock(&vars->fork_mutex[id]);
	}
}