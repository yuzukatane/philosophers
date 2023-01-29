/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:30:43 by kyuzu             #+#    #+#             */
/*   Updated: 2023/01/29 16:40:19 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

# define SUCCESS 1
# define FAIL -1
# define NOT_EXIST -2

typedef struct s_arg
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_num;
	int	time_to_think;
}	t_arg;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_philo_state;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				nb_philo_total;
	int				must_eat_num;
	int				*total_meal_num;
	struct timeval	*start_time;
	size_t			last_eat;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*ready_to_start;
	bool			*simulation_over;
	t_arg			*arg;
	t_philo_state	state;

}	t_philo;

typedef struct s_info
{
	struct timeval	start_time;
	int				num_philo;
	int				time_to_die;
	t_philo			*philo;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	ready_to_start;
	bool			simulation_over;
	int				total_meals;
}	t_info;

typedef enum e_wich_fork
{
	LEFT,
	RIGHT,
	BOTH
}	t_wich_fork;

bool		check_args(int argc, char *argv[], t_arg *arg);
size_t		get_time(struct timeval start);
int			init_info(t_info *info, t_arg *arg);
void		init_philo(t_info *info, t_arg *arg);
long long	to_int(const char *str);

void		*action(void *arg);
bool		print_msg(t_philo *philo, char *msg);

bool		take_forks(t_philo *philo);
void		release_forks(t_philo *philo, t_wich_fork forks_to_release);

void		monitoring(t_info *info);

#endif
