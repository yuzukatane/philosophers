/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:06:32 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/30 11:12:04 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_simulation(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->mutex_fork[i]);
		i++;
	}
	free(info->philo);
	free(info->mutex_fork);
	pthread_mutex_destroy(&info->mutex_print);
	pthread_mutex_destroy(&info->ready_to_start);
}

void	monitoring(t_info *info)
{
	int	i;

	pthread_mutex_unlock(&info->ready_to_start);
	while (1)
	{
		i = -1;
		while (++i < info->num_philo)
		{
			pthread_mutex_lock(&info->mutex_print);
			if ((info->total_meals != INT_MIN && info->total_meals <= 0)
				|| get_time(info->start_time) - info->philo[i].last_eat
				> (unsigned long)info->time_to_die)
			{
				if (info->total_meals > 0 || info->total_meals == INT_MIN)
					printf("%ld %d %s\n", get_time(info->start_time)
						/ 1000, info->philo[i].philo_id, "died");
				info->simulation_over = true;
				pthread_mutex_unlock(&info->mutex_print);
				return (end_simulation(info));
			}
			pthread_mutex_unlock(&info->mutex_print);
		}
		usleep(100);
	}
}
