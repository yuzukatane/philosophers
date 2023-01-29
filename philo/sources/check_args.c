/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:41:02 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 16:08:44 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <limits.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	to_int(const char *str)
{
	long long	number;

	if (*str == '\0' || *str == '+' || *str == '-')
		return (FAIL);
	number = 0;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (FAIL);
		number *= 10;
		number += (*str - '0');
		if (INT_MAX < number)
			return (FAIL);
		str++;
	}
	return (number);
}

bool	check_args(int argc, char *argv[], t_arg *arg)
{
	if (!(argc == 5 || argc == 6))
		return (false);
	arg->num_philo = to_int(argv[1]);
	arg->time_to_die = to_int(argv[2]) * 1000;
	arg->time_to_eat = to_int(argv[3]) * 1000;
	arg->time_to_sleep = to_int(argv[4]) * 1000;
	if (argc == 6)
		arg->must_eat_num = to_int(argv[5]);
	else
		arg->must_eat_num = NOT_EXIST;
	if (arg->num_philo < 0 || 200 < arg->num_philo || arg->time_to_die < 0
		|| arg->time_to_eat < 0 || arg->time_to_sleep < 0
		|| arg->must_eat_num == FAIL)
		return (false);
	if (arg->time_to_eat < arg->time_to_sleep)
		arg->time_to_think
			= (arg->time_to_die - arg->time_to_eat + arg->time_to_sleep) / 2;
	else
		arg->time_to_think = (arg->time_to_die - (arg->time_to_eat * 2)) / 2;
	if (arg->time_to_think < 0)
		arg->time_to_think = 0;
	return (true);
}
