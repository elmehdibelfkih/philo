/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:23:50 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/07/20 03:02:28 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			si;
	long long	re;

	i = 0;
	re = 0;
	si = 1;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' )
	{		
		si = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		re = re * 10 + (str[i++] - 48);
	return (re * si);
}
