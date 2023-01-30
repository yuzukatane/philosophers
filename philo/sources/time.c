/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:04:50 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/30 11:33:59 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(struct timeval start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec)));
}

void	update_time(t_philo *philo)
{
	philo->current_time_us = get_time(*philo->start_time);
	philo->current_time_ms = philo->current_time_us / 1000;
}

void	sleep_until(t_philo *philo, size_t time_to_awake)
{
	while (1)
	{
		update_time(philo);
		if (philo->current_time_us > time_to_awake)
			return ;
		usleep(5);
	}
}
