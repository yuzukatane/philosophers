/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:31:42 by kyuzu             #+#    #+#             */
/*   Updated: 2023/02/13 12:16:12 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	int		i;
	t_info	info;
	t_arg	arg;

	if (check_args(argc, argv, &arg) == false)
		return (0);
	if (init_info(&info, &arg) == false)
		return (0);
	init_philo(&info, &arg);
	i = 0;
	while (i < info.num_philo)
	{
		pthread_create(&info.philo[i].thread_id, NULL, action, &info.philo[i]);
		i++;
	}
	gettimeofday(&info.start_time, NULL);
	monitoring(&info);
	return (0);
}
