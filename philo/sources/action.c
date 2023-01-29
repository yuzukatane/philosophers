/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:01:53 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 16:36:13 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	eating(t_philo *philo)
{
	if (take_forks(philo) == false)
		return (false);
	philo->state = EATING;
	if (print_msg(philo, "is eating") == false)
		return (false);
	usleep(philo->arg->time_to_eat);
	release_forks(philo, BOTH);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	if (print_msg(philo, "is sleeping") == false)
		return (false);
	usleep(philo->arg->time_to_sleep);
	return (true);
}

bool	thinking(t_philo *philo)
{
	philo->state = THINKING;
	if (print_msg(philo, "is thinking") == false)
		return (false);
	usleep(philo->arg->time_to_think);
	return (true);
}

bool	wait_before_start(t_philo *philo)
{
	pthread_mutex_lock(philo->ready_to_start);
	pthread_mutex_unlock(philo->ready_to_start);
	if (philo->philo_id % 2 == 0)
	{
		if (print_msg(philo, "is thinking") == false)
			return (false);
		usleep(500);
	}
	return (true);
}

void	*action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (wait_before_start(philo) == false)
		return (NULL);
	while (1)
	{
		if (eating(philo) == false)
			break ;
		if (sleeping(philo) == false)
			break ;
		if (thinking(philo) == false)
			break ;
	}
	return (NULL);
}
