/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:20:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/20 22:32:23 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	read_input(t_vars *vars, char **av)
{
	vars->j = 0;
	vars->nb_of_eat = INT_MAX;
	while (av[++vars->j])
	{
		vars->i = -1;
		while (av[vars->j][++vars->i])
			if (!ft_isdigit(av[vars->j][vars->i]))
				return (0);
		if (vars->j == 1)
			vars->n_philo = ft_atoi(av[1]);
		else if (vars->j == 2)
			vars->t_die = ft_atoi(av[2]);
		else if (vars->j == 3)
			vars->t_eat = ft_atoi(av[3]);
		else if (vars->j == 4)
			vars->t_sleep = ft_atoi(av[4]);
		else if (vars->j == 5)
			vars->nb_of_eat = ft_atoi(av[5]);
	}
	if (vars->t_die <= 0 || vars->t_eat <= 0 || vars->t_sleep <= 0
		|| vars->n_philo <= 0 || vars->nb_of_eat <= 0 || vars->n_philo > 200)
		return (0);
	if (vars->nb_of_eat == INT_MAX)
		vars->nb_of_eat = -1;
	return (init_data(vars));
}

int	init_data(t_vars *vars)
{
	vars->philos = malloc(sizeof(t_philo) * vars->n_philo);
	if (!vars->philos)
		return (0);
	vars->fork_mutex = malloc(sizeof(pthread_mutex_t) * vars->n_philo);
	if (!vars->fork_mutex)
		return (free(vars->philos), 0);
	vars->x = -1;
	while (++vars->x < vars->n_philo)
		pthread_mutex_init(&vars->fork_mutex[vars->x], NULL);
	pthread_mutex_init(&vars->mutex, NULL);
	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->death, NULL);
	vars->x = -1;
	while (++vars->x < vars->n_philo)
	{
		vars->philos[vars->x].data = vars;
		vars->philos[vars->x].id = vars->x + 1;
		vars->philos[vars->x].nb_eat = 0;
		vars->philos[vars->x].st = 0;
		vars->state = 1;
		vars->philos[vars->x].last_eat = c_t();
	}
	vars->s_t = c_t();
	return (1);
}

void	f_lock(int lu, int id, t_vars *vars)
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

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			si;
	long long	re;

	i = 0;
	re = 0;
	si = 1;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' )
	{		
		si = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		re = re * 10 + (str[i++] - 48);
		if ((re * si) < -2147483648 || (re * si) > 2147483647)
			return (0);
	}
	return (re * si);
}
