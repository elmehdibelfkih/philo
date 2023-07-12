/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/11 00:41:41 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long long c_time(void)
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
    printf("%d \n", p.id);
    return (arg);
}

int creat_philos(t_vars *vars)
{
    int i;

    i = 0;
    while (i < vars->nb_of_philo)
    {
        pthread_create(&vars->philos[i].philo, NULL, &routine, &vars->philos[i]);
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
    // printf("%lld", c_time());
    creat_philos(&vars);
    vars.x = 0; 
}

