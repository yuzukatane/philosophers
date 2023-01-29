/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:03:56 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 16:05:32 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (print_msg(philo, "has taken a fork") == false
		|| philo->nb_philo_total < 2)
	{
		release_forks(philo, philo->philo_id % 2 == 0);
		return (false);
	}	
	if (philo->philo_id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (print_msg(philo, "has taken a fork") == false)
	{
		release_forks(philo, BOTH);
		return (false);
	}
	return (true);
}

void	release_forks(t_philo *philo, t_wich_fork forks_to_release)
{
	if (forks_to_release == RIGHT || forks_to_release == BOTH)
		pthread_mutex_unlock(philo->right_fork);
	if (forks_to_release == LEFT || forks_to_release == BOTH)
		pthread_mutex_unlock(philo->left_fork);
}
