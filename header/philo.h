/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:55:22 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/20 04:09:46 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	long long		last_eat;
	int				nb_eat;
	pthread_t		philo;
	struct s_vars	*data;
}				t_philo;
typedef struct s_vars
{
	unsigned short int	n_philo;
	int					nb_of_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	s_t;
	t_philo				*philos;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		mutex;
	pthread_mutex_t		print;
	pthread_mutex_t		death;
	short int			state;
	short int			i;
	short int			j;
	short int			x;
	short int			y;
	short int			z;
}				t_vars;

int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					read_input(t_vars *vars, char **av);
int					init_data(t_vars *vars);
unsigned long long	c_t(void);
int					creat_philos(t_vars *vars);
int					ft_usleep(unsigned int t, t_vars *vars);
void				*routine(void *arg);
void				f_lock(int lu, int id, t_vars *vars);
void				m_free(t_vars *vars);
int					eat(t_philo *p);
int					join_philos(t_vars *vars);

#endif
