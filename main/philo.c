/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/17 06:27:38 by ebelfkih         ###   ########.fr       */
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
    t_philo *p;

    p = &(*(t_philo *)arg);
    if (!(p->id%2))
        usleep(100);
    while (1) 
    {
        mu_lock(1, p->id, p->data);
        pthread_mutex_lock(&p->data->mutex);
	    p->nb_eat += 1;
	    p->last_eat = c_time();
        pthread_mutex_unlock(&p->data->mutex);
        pthread_mutex_lock(&p->data->print);
	    printf("%lld philo %d has taken a fork\n", (c_time() - p->data->start_time), p->id);
	    printf("%lld philo %d has taken a fork\n", (c_time() - p->data->start_time), p->id);
	    printf("%lld philo %d is eating\n", (c_time() - p->data->start_time), p->id);
        pthread_mutex_unlock(&p->data->print);
	    ft_usleep(p->data->time_to_eat);
        mu_lock(0, p->id, p->data);
        pthread_mutex_lock(&p->data->print);
	    printf("%lld philo %d is sleeping\n",(c_time() - p->data->start_time), p->id);
        pthread_mutex_unlock(&p->data->print);
	    ft_usleep(p->data->time_to_sleep);
        pthread_mutex_lock(&p->data->print);
        printf("%lld philo %d is thinking\n",(c_time() - p->data->start_time), p->id);
        pthread_mutex_unlock(&p->data->print);
    }
    return (arg);
}

void	ft_usleep(unsigned int t)
{
	unsigned long long	tt;

	tt = c_time();
	while (c_time() < tt + t)
		usleep(50);
}

int creat_philos(t_vars *vars)
{
    int i;

    i = -1;
    while (++i < vars->nb_of_philo)
    {
        pthread_create(&vars->philos[i].philo, NULL, &routine, &vars->philos[i]);
        
    }
    
    return (1);
}

int who_died(t_vars *vars)
{
    vars->x = 0;
    int c;
    while (vars->x < vars->nb_of_philo)
    {
        c = 0;
        pthread_mutex_lock(&vars->mutex);
        if (vars->philos[vars->x].nb_eat <= vars->nb_of_eat)
            c = 1;
        if ((vars->philos[vars->x].last_eat + vars->time_to_die) < (c_time()))
        {
            pthread_mutex_lock(&vars->print);
            printf("%lld philo %d died\n", c_time() - vars->start_time ,vars->philos[vars->x].id);
            return  0;
        }  
        pthread_mutex_unlock(&vars->mutex);
        vars->x++;
        usleep(100);
    }
    if (c == 0  && vars->nb_of_eat != -1)
        return 0;
    return (1);      
}

void m_free(t_vars *vars)
{
    free(vars->philos);
    free(vars->fork_mutex);
    vars->x = -1;
	while (++vars->x < vars->nb_of_philo)
        pthread_mutex_destroy(&vars->fork_mutex[vars->x]);
    vars->x = -1;
    while (++vars->x < vars->nb_of_philo)
        pthread_detach(vars->philos[vars->x].philo);
}

int main(int ac, char **av)
{
    t_vars  vars;

    vars.y = 0;
    if ((ac != 5 && ac != 6) || !read_input(&vars, av))
        return (exit_message(&vars, 0));
    creat_philos(&vars);
    while (who_died(&vars));
    // m_free(&vars);
    
}

