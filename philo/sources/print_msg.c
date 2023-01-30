/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:03:28 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/30 11:10:12 by kyuzu            ###   ########.fr       */
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
	update_time(philo);
	if (philo->state == EATING)
	{
		philo->last_eat = philo->current_time_us;
		if (philo->must_eat_num != INT_MIN && philo->must_eat_num > 0)
		{
			philo->must_eat_num--;
			*(philo->total_meal_num) -= 1;
		}
	}
	printf("%ld %d %s\n", philo->current_time_ms, philo->philo_id, msg);
	pthread_mutex_unlock(philo->mutex_print);
	return (true);
}
