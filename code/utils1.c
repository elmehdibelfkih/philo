/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:23:50 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/21 04:37:29 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

unsigned long long	c_t(void)
{
	long long		t;
	struct timeval	cu_time;

	gettimeofday(&cu_time, NULL);
	t = cu_time.tv_sec * 1000 + cu_time.tv_usec / 1000;
	return (t);
}

int	ft_usleep(unsigned int t, t_vars *vars)
{
	unsigned long long	tt;
	short int			i;

	tt = c_t();
	while (c_t() < tt + t)
	{
		pthread_mutex_lock(&vars->death);
		i = vars->state;
		pthread_mutex_unlock(&vars->death);
		if (i == 0)
			return (0);
		usleep(50);
	}
	return (1);
}

int	creat_join_philos(t_vars *vars, int j)
{
	short int	i;

	i = -1;
	if (j == 0)
	{
		while (++i < vars->n_philo)
			pthread_create(&vars->philos[i].philo, NULL,
				&routine, &vars->philos[i]);
		return (1);
	}
	else
	{
		while (++i < vars->n_philo)
			pthread_join(vars->philos[i].philo, NULL);
		return (1);
	}
}

void	one_philo(t_vars *vars)
{
	pthread_mutex_lock(&vars->print);
	printf("%lld philo %d has taken a fork\n", (c_t() - vars->s_t),
		vars->philos[0].id);
	pthread_mutex_unlock(&vars->print);
	if (ft_usleep(vars->t_die, vars) == 0)
		return ;
}

void	m_free(t_vars *vars)
{
	vars->x = -1;
	while (++vars->x < vars->n_philo)
		pthread_mutex_destroy(&vars->fork_mutex[vars->x]);
	pthread_mutex_destroy(&vars->mutex);
	pthread_mutex_destroy(&vars->print);
	pthread_mutex_destroy(&vars->death);
	free (vars->philos);
	free (vars->fork_mutex);
	vars->x = -1;
}
