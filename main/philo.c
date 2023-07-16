/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/16 04:32:23 by ebelfkih         ###   ########.fr       */
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
    t_philo *philosopher;

    philosopher = &(*(t_philo *)arg);
    if (!(philosopher->id%2))
        usleep(100);
    while (1) 
    {
        mu_lock(1, philosopher->id, philosopher->data);
	    philosopher->last_eat = c_time();
	    printf("%lld philo %d has taken a fork\n", (c_time() - philosopher->data->start_time), philosopher->id);
	    printf("%lld philo %d has taken a fork\n", (c_time() - philosopher->data->start_time), philosopher->id);
	    philosopher->nb_eat += 1;
	    printf("%lld philo %d is eating\n", (c_time() - philosopher->data->start_time), philosopher->id);
	    ft_usleep(philosopher->data->time_to_eat);
        mu_lock(0, philosopher->id, philosopher->data);
	    printf("%lld philo %d is sleeping\n",(c_time() - philosopher->data->start_time), philosopher->id);
	    ft_usleep(philosopher->data->time_to_sleep);
        printf("%lld philo %d is thinking\n",(c_time() - philosopher->data->start_time), philosopher->id);
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

void	activities(t_philo *philosopher)
{
	mu_lock(1, philosopher->id, philosopher->data);
    printf("%lld | %lld \n", philosopher->data->time_to_eat, philosopher->data->time_to_sleep);
	printf("%lld philo %d has taken a fork\n", (c_time() - philosopher->data->start_time), philosopher->id);
	printf("%lld philo %d has taken a fork\n", (c_time() - philosopher->data->start_time), philosopher->id);
	philosopher->last_eat = c_time();
	philosopher->nb_eat += 1;
	printf("%lld philo %d is eating\n", (c_time() - philosopher->data->start_time), philosopher->id);
	ft_usleep(philosopher->data->time_to_eat);
    mu_lock(0, philosopher->id, philosopher->data);
	printf("%lld philo %d is sleeping\n",(c_time() - philosopher->data->start_time), philosopher->id);
	ft_usleep(philosopher->data->time_to_sleep);
    printf("%lld philo %d is thinking\n",(c_time() - philosopher->data->start_time), philosopher->id);
}

int creat_philos(t_vars *vars)
{
    int i;

    i = -1;
    while (++i < vars->nb_of_philo)
        pthread_create(&vars->philos[i].philo, NULL, &routine, &vars->philos[i]);
    return (1);
}

int who_died(t_vars *vars)
{
    vars->x = 0;
    while (vars->x < vars->nb_of_philo)
    {
        if ((vars->philos[vars->x].last_eat + vars->time_to_die) < (c_time()))
        {
            // printf("dead%lld\n",vars->philos[vars->x].last_eat );
            // printf("dead b nakis %lld\n", c_time() - vars->philos[vars->x].last_eat);
            // printf("dead%lld\n",c_time());
            printf("%lld philo %d died\n", c_time() - vars->start_time ,vars->philos[vars->x].id);
            return  0;
        }  
        vars->x++;
        usleep(100);
    }
    return (1);      
}

int main(int ac, char **av)
{
    t_vars  vars;

    vars.y = 0;
    if ((ac != 5 && ac != 6) || !read_input(&vars, av))
        return (exit_message(&vars, 0));
    creat_philos(&vars);
    while (who_died(&vars));
      
    

}

