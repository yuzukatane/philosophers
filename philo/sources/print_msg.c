/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:28 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 16:05:10 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->mutex_print);
	if (*philo->simulation_over == true)
	{
		pthread_mutex_unlock(philo->mutex_print);
		return (false);
	}
	if (philo->state == EATING)
	{
		philo->last_eat = get_time(*(philo->start_time));
		if (philo->must_eat_num != INT_MIN && philo->must_eat_num > 0)
		{
			philo->must_eat_num--;
			*(philo->total_meal_num) -= 1;
		}
	}
	printf("%ld %d %s\n",
		get_time(*(philo->start_time)) / 1000, philo->philo_id, msg);
	pthread_mutex_unlock(philo->mutex_print);
	return (true);
}
