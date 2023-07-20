/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/20 03:10:05 by ebelfkih         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo		*p;
	short int	i;

	p = &(*(t_philo *)arg);
	if (!(p->id % 2))
		ft_usleep(p->data->time_to_eat - 1, p->data);
	pthread_mutex_lock(&p->data->death);
		i = p->data->state;
	pthread_mutex_unlock(&p->data->death);
	while (i)
	{
		pthread_mutex_lock(&p->data->death);
		i = p->data->state;
		pthread_mutex_unlock(&p->data->death);
		if (eat(p) == 0)
			return (arg);
		pthread_mutex_lock(&p->data->print);
		printf("%lld philo %d is sleeping\n", (c_t() - p->data->s_t), p->id);
		pthread_mutex_unlock(&p->data->print);
		if (ft_usleep(p->data->time_to_sleep, p->data) == 0)
			return (arg);
		pthread_mutex_lock(&p->data->print);
		printf("%lld philo %d is thinking\n", (c_t() - p->data->s_t), p->id);
		pthread_mutex_unlock(&p->data->print);
	}
	return (arg);
}

int	eat(t_philo *p)
{
	mu_lock(1, p->id, p->data);
	pthread_mutex_lock(&p->data->mutex);
	p->nb_eat += 1;
	p->last_eat = c_t();
	pthread_mutex_unlock(&p->data->mutex);
	pthread_mutex_lock(&p->data->print);
	printf("%lld philo %d has taken a fork\n", (c_t() - p->data->s_t), p->id);
	pthread_mutex_unlock(&p->data->print);
	pthread_mutex_lock(&p->data->print);
	printf("%lld philo %d has taken a fork\n", (c_t() - p->data->s_t), p->id);
	pthread_mutex_unlock(&p->data->print);
	pthread_mutex_lock(&p->data->print);
	printf("%lld philo %d is eating\n", (c_t() - p->data->s_t), p->id);
	pthread_mutex_unlock(&p->data->print);
	if (ft_usleep(p->data->time_to_eat, p->data) == 0)
	{
		mu_lock(0, p->id, p->data);
		return (0);
	}
	mu_lock(0, p->id, p->data);
	return (1);
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

int	creat_philos(t_vars *vars)
{
	short int	i;

	i = -1;
	while (++i < vars->n_philo)
	{
		pthread_create(&vars->philos[i].philo, NULL, &routine, &vars->philos[i]);
		// pthread_detach(vars->philos[i].philo);
	}
	return (1);
}

int	join_philos(t_vars *vars)
{
	short int	i;

	i = -1;
	while (++i < vars->n_philo)
	{
		pthread_join(vars->philos[i].philo, NULL);
	}
	return (1);
}

int	who_died(t_vars *vars)
{
	int	c;

	vars->x = 0;
	while (vars->x < vars->n_philo)
	{
		c = 0;
		pthread_mutex_lock(&vars->mutex);
		if (vars->philos[vars->x].nb_eat < vars->nb_of_eat)
			c = 1;
		if ((vars->philos[vars->x].last_eat + vars->time_to_die) <= (c_t()))
		{
			pthread_mutex_lock(&vars->death);
				vars->state = 0;
			pthread_mutex_unlock(&vars->death);
			join_philos(vars);
			pthread_mutex_lock(&vars->print);
			printf("%lld philo %d died\n", c_t() - vars->s_t, vars->philos[vars->x].id);
			pthread_mutex_unlock(&vars->print);
			pthread_mutex_unlock(&vars->mutex);
			return (0);
		}
		pthread_mutex_unlock(&vars->mutex);
		vars->x++;
	}
	if (c == 0 && vars->nb_of_eat != -1)
		return (0);
	return (1);
}

void	m_free(t_vars *vars)
{
	vars->x = -1;
	while (++vars->x < vars->n_philo)
		pthread_mutex_destroy(&vars->fork_mutex[vars->x]);
	free (vars->philos);
	free (vars->fork_mutex);
	vars->x = -1;
}

int	main(int ac, char **av)
{
	t_vars	vars;

	vars.y = 0;
	if ((ac != 5 && ac != 6) || !read_input(&vars, av))
		return(printf("error: bad arguments\n"));
	creat_philos(&vars);
	while (who_died(&vars))
		usleep(100);;
	m_free(&vars);
	return (0);
}
