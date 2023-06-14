/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:55:22 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/06/07 20:42:50 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

typedef struct s_vars {

	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eat;
	int				*forks;
	pthread_t		*philo;
	int				*eat_counter;
	// int		dead;
	// int		*last_eat;
	// int		*is_eating;
	// int		start;
	// pthread_mutex_t	*mutex;
	// pthread_mutex_t	print;
	// pthread_mutex_t	dead_mutex;
	// pthread_mutex_t	*fork_mutex;
	// pthread_t		monitor;
}				t_vars;

typedef struct s_l_vars {

	int		i;
	int		j;
	int		x;
	int		y;
	int		z;
}				t_l_vars;


int		exit_message(t_vars *m, int i);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		read_input(t_vars *vars, t_l_vars *l, char **av);
int		init_data(t_vars *vars, t_l_vars *l);
int		ft_clear(char **spl, int p);

#endif