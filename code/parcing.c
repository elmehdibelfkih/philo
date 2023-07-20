/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:20:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/20 03:10:43 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	read_input(t_vars *vars, char **av)
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
		if (vars->j == 1)
			vars->n_philo = ft_atoi(av[1]);
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
	if (vars->n_philo <= 0 || vars->nb_of_eat == 0 || vars->n_philo > 200)
		return (0);
	vars->philos = malloc(sizeof(t_philo) * vars->n_philo);
	vars->fork_mutex = malloc(sizeof(pthread_mutex_t) * vars->n_philo);
	vars->x = -1;
	while (++vars->x < vars->n_philo)
		pthread_mutex_init(&vars->fork_mutex[vars->x], NULL);
	pthread_mutex_init(&vars->mutex, NULL);
	pthread_mutex_init(&vars->print, NULL);
	vars->x = 0;
	while (vars->x < vars->n_philo)
	{
		vars->philos[vars->x].data = vars;
		vars->philos[vars->x].id = vars->x + 1;
		vars->philos[vars->x].nb_eat = 0;
		vars->state = 1;
		vars->philos[vars->x].last_eat = c_t();
		vars->x++;
	}
	vars->s_t = c_t();
	return (1);
}

void	mu_lock(int lu, int id, t_vars *vars)
{
	if (lu == 1)
	{
		pthread_mutex_lock(&vars->fork_mutex[id - 1]);
		pthread_mutex_lock(&vars->fork_mutex[id % vars->n_philo]);
	}
	else
	{
		pthread_mutex_unlock(&vars->fork_mutex[id - 1]);
		pthread_mutex_unlock(&vars->fork_mutex[id % vars->n_philo]);
	}
}
