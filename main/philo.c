/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/15 05:28:32 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

unsigned long long c_time(void)
{
    long long t;
    struct timeval cu_time;
    gettimeofday(&cu_time, NULL);
    t = cu_time.tv_sec*1000 + cu_time.tv_usec/1000;
    return (t);
}

void *routine(void *arg)
{
    t_philo p;

    p = *(t_philo *)arg;
    if (!p.id%2)
    {
        usleep(100);
    }
    while (1) 
        activities(&p);
    return (arg);
}

void	ft_usleep(unsigned int t)
{
	unsigned long long	tt;

	tt = c_time();
	while (c_time() < tt + t)
		usleep(50);
}

void	activities(t_philo *philosopher)
{
    // pthread_mutex_lock(&philosopher->data->mutex);
    // if (philosopher->id%2)
    // {
    //     usleep(200);
    // }
	mu_lock(1, philosopher->id, philosopher->data);
	printf("%lld philo %d has taken a fork\n", c_time() - philosopher->data->start_date, philosopher->id);
	printf("%lld philo %d has taken a fork\n", c_time() - philosopher->data->start_date, philosopher->id);
	philosopher->state = 1;
	philosopher->nb_eat += 1;
	printf("%lld philo %d is eating\n", c_time() - philosopher->data->start_date, philosopher->id);
	philosopher->last_eat = c_time();
	ft_usleep(philosopher->data->time_to_eat);
    mu_lock(0, philosopher->id, philosopher->data);
    // pthread_mutex_unlock(&philosopher->data->mutex);
	philosopher->state = 0;
	// if (philosopher->eat_number >= philosopher->arg->nb_must_eat
	// 	&& philosopher->arg->nb_must_eat != 0)
	// 	return ;
	printf("%lld philo %d is sleeping\n",c_time() - philosopher->data->start_date, philosopher->id);
	ft_usleep(philosopher->data->time_to_sleep);
    printf("%lld philo %d is thinking\n",c_time() - philosopher->data->start_date, philosopher->id);
}

int creat_philos(t_vars *vars)
{
    int i;

    i = 0;
    vars->start_date = c_time();
    while (i < vars->nb_of_philo)
    {
        pthread_create(&vars->philos[i].philo, NULL, &routine, &vars->philos[i]);
        ft_usleep(2);
        i++;
    }
    i = 0;
    while (i < vars->nb_of_philo)
    {
        pthread_join(vars->philos[i].philo, NULL);
        i++;
    }
    return 1;
    
}

int main(int ac, char **av)
{
    t_vars  vars;

    vars.y = 0;
    if ((ac != 5 && ac != 6) || !read_input(&vars, av))
        return (exit_message(&vars, 0));
    creat_philos(&vars);

}

