/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:55:22 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/10 23:57:48 by ebelfkih         ###   ########.fr       */
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

typedef struct s_philo
{
	short int		id;
	long long		start_date;
	long long		last_eat;
	int				nb_eat;
	pthread_t		philo;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	struct s_vars	*data;
}				t_philo;

typedef struct s_vars 
{
	long long	nb_of_philo;
	long long	nb_of_eat;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	t_philo		*philos;  
	pthread_mutex_t	*fork_mutex;
	short int	i;
	short int	j;
	short int	x;
	short int	y;
}				t_vars;


int		exit_message(t_vars *m, int i);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		read_input(t_vars *vars, char **av);
int		init_data(t_vars *vars);
long long c_time(void);

#endif