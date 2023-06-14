/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:20:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/06/07 20:46:00 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int    read_input(t_vars *vars, t_l_vars *l, char **av)
{
	l->j = 0;
	vars->nb_of_eat = -1;
    while (av[++l->j])
	{
		l->i = -1;
		while (av[l->j][++l->i])
		{
			if (!ft_isdigit(av[l->j][l->i]))
				return (0);
		}
		if(l->j == 1)
			vars->nb_of_philo = ft_atoi(av[1]);
		else if (l->j == 2)
			vars->time_to_die = ft_atoi(av[2]);
		else if (l->j == 3)
			vars->time_to_eat = ft_atoi(av[3]);
		else if (l->j == 4)
			vars->time_to_sleep = ft_atoi(av[4]);
		else if (l->j == 5)
			vars->nb_of_eat = ft_atoi(av[5]);
	}
	return (init_data(vars, l));
}

int	init_data(t_vars *vars, t_l_vars *l)
{
	l->x = 0;
	if (!(vars->forks = malloc(sizeof(int) * vars->nb_of_philo)))
		return (0);
	while(l->x < vars->nb_of_philo)
		vars->forks[l->x++] = 1;
	if (!(vars->eat_counter = malloc(sizeof(int) * vars->nb_of_philo)))
		return (free(vars->forks), 0);
	l->x = 0;
	while(l->x < vars->nb_of_philo)
		vars->eat_counter[l->x++] = 0;
	if (!(vars->philo = malloc(sizeof(pthread_t) * vars->nb_of_philo)))
		return (free(vars->forks), free(vars->eat_counter), 0);
	return (1);
}

// int	ft_clear(char **spl, int p)
// {
// 	int	i;
// 	i = 0;
// 	while (i < p && spl[i])
// 		free(spl[i++]);
// 	free(spl);
// 	return (0);
// }