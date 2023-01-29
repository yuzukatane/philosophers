/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:57:28 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 15:59:22 by kyuzu            ###   ########.fr       */
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

int	init_info(t_info *info, t_arg *arg)
{
	int	i;

	info->num_philo = arg->num_philo;
	info->time_to_die = arg->time_to_die;
	info->simulation_over = false;
	if (arg->must_eat_num == NOT_EXIST)
		info->total_meals = INT_MIN;
	else
		info->total_meals = arg->must_eat_num * info->num_philo;
	info->philo = malloc(sizeof(t_philo) * info->num_philo);
	if (info->philo == NULL)
		return (false);
	info->mutex_fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (info->mutex_fork == NULL)
	{
		free(info->philo);
		return (false);
	}
	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_init(&info->mutex_fork[i], NULL);
	pthread_mutex_init(&info->mutex_print, NULL);
	pthread_mutex_init(&info->ready_to_start, NULL);
	pthread_mutex_lock(&info->ready_to_start);
	return (true);
}

void	init_philo(t_info *info, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].arg = arg;
		info->philo[i].must_eat_num = arg->must_eat_num;
		info->philo[i].total_meal_num = &info->total_meals;
		info->philo[i].simulation_over = &info->simulation_over;
		info->philo[i].nb_philo_total = info->num_philo;
		info->philo[i].philo_id = i + 1;
		info->philo[i].start_time = &info->start_time;
		info->philo[i].mutex_print = &info->mutex_print;
		info->philo[i].ready_to_start = &info->ready_to_start;
		info->philo[i].left_fork = &info->mutex_fork[i];
		if (i != info->num_philo - 1)
			info->philo[i].right_fork = &info->mutex_fork[i + 1];
		else
			info->philo[i].right_fork = &info->mutex_fork[0];
		i++;
	}
}
