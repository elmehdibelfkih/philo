/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:58:52 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/06/07 20:37:58 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int main(int ac, char **av)
{
    t_vars  vars;
    t_l_vars  l;

    l.y = 0;
    if ((ac != 5 && ac != 6) || !read_input(&vars, &l, av))
        return (exit_message(&vars, 0));
    printf("number_of_philosophers                    : %d\n", vars.nb_of_philo);
    printf("time_to_die                               : %d\n", vars.time_to_die);
    printf("time_to_eat                               : %d\n", vars.time_to_eat);
    printf("time_to_sleep                             : %d\n", vars.time_to_sleep);
    printf("number_of_times_each_philosopher_must_eat : %d\n", vars.nb_of_eat);
    while(l.y < vars.nb_of_philo)
        printf("%d\n", vars.forks[l.y++]);
    return (0);
}