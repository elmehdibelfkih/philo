/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/08/07 18:49:00 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*routine(void *arg)
{
	t_philo		*p;

	p = &(*(t_philo *)arg);
	if (!(p->id % 2))
		ft_usleep(1 / 100, p->data);
	p->lp = 1;
	if (p->data->n_philo == 1)
		return (one_philo(p->data), arg);
	while (p->lp)
	{
		pthread_mutex_lock(&p->data->death);
		p->lp = p->data->state;
		pthread_mutex_unlock(&p->data->death);
		if (eat(p) == 0)
			return (arg);
		pthread_mutex_lock(&p->data->print);
		printf("%lld philo %d is sleeping\n", (c_t() - p->data->s_t), p->id);
		pthread_mutex_unlock(&p->data->print);
		if (ft_usleep(p->data->t_sleep, p->data) == 0)
			return (arg);
		pthread_mutex_lock(&p->data->print);
		printf("%lld philo %d is thinking\n", (c_t() - p->data->s_t), p->id);
		pthread_mutex_unlock(&p->data->print);
	}
	return (arg);
}

int	eat(t_philo *p)
{
	f_lock(1, p->id, p->data);
	pthread_mutex_lock(&p->data->mutex);
	p->nb_eat += 1;
	p->last_eat = c_t();
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_lock(&p->data->print);
	pthread_mutex_lock(&p->data->death);
	if (p->data->state == 0)
		return (pthread_mutex_unlock(&p->data->death),
			pthread_mutex_unlock(&p->data->print),f_lock(1, p->id, p->data), 0);
	pthread_mutex_unlock(&p->data->death);
	printf("%lld philo %d has taken a fork\n", (c_t() - p->data->s_t), p->id);
	printf("%lld philo %d has taken a fork\n", (c_t() - p->data->s_t), p->id);
	printf("%lld philo %d is eating\n", (c_t() - p->data->s_t), p->id);
	pthread_mutex_unlock(&p->data->print);
	if (ft_usleep(p->data->t_eat, p->data) == 0)
		return (f_lock(0, p->id, p->data), 0);
	f_lock(0, p->id, p->data);
	pthread_mutex_lock(&p->data->mutex);
	if ((p->nb_eat == p->data->nb_of_eat + 1) && p->data->nb_of_eat != -1)
	{
		p->st = 1;
		return (pthread_mutex_unlock(&p->data->mutex), 0);
	}
	return (pthread_mutex_unlock(&p->data->mutex), 1);
}

int	who_died(t_vars *vars)
{
	int	c;

	vars->x = 0;
	while (vars->x < vars->n_philo)
	{
		c = 0;
		pthread_mutex_lock(&vars->mutex);
		if (vars->philos[vars->x].st == 0)
			c = 1;
		if (((vars->philos[vars->x].last_eat + vars->t_die) < (c_t()))
			|| (c == 0 && vars->nb_of_eat != -1))
		{
			action(vars, c);
			return (0);
		}
		pthread_mutex_unlock(&vars->mutex);
		vars->x++;
	}
	return (1);
}

void	action(t_vars *vars, int c)
{
	pthread_mutex_lock(&vars->death);
		vars->state = 0;
	pthread_mutex_unlock(&vars->death);
	pthread_mutex_unlock(&vars->mutex);
	creat_join_philos(vars, 1);
	pthread_mutex_lock(&vars->print);
	if (!(c == 0 && vars->nb_of_eat != -1))
		printf("%lld philo %d died\n", c_t() - vars->s_t,
			vars->philos[vars->x].id);
	pthread_mutex_unlock(&vars->print);
	return ;
}

int	main(int ac, char **av)
{
	t_vars	vars;

	vars.y = 0;
	if ((ac != 5 && ac != 6) || !read_input(&vars, av))
		return (printf("error: bad arguments\n"));
	creat_join_philos(&vars, 0);
	while (who_died(&vars))
		usleep(100);
	m_free(&vars);
	return (0);
}
