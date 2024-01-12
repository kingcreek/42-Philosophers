/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:54:26 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 01:15:34 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

# define FORK	0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define DEAD	4

typedef struct s_init_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			tv_sec;
	int				tv_usec;
	int				any_dead;
	char			*shared_fork;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	**fork_mutex;
	pthread_mutex_t	any_dead_mutex;
	pthread_mutex_t	print_mutex;
}t_data;

typedef struct s_philo
{
	int				last_eat;
	int				last_eat_priv;
	int				id;
	int				eat_count;
	int				forks;
	t_data			*init_data;
	pthread_mutex_t	last_eat_mutex;
}t_philo;

/* UTILS */
int		ft_atoi(const char *str);
void	msleep(int time);
int		get_time(t_data *data);
void	wait_until(t_data *data, int time);

/* MESSAGES */
int		print_philo_msg(t_data *data, int philo_id, int msg_nbr);
void	print_invalid(int msg_nbr);

/* PARSER */
int		start_init(int argc, char **argv, t_data *data);

/* ACTIONS */
int		sleeping(t_data *data, t_philo *philo);
void	putdown_fork(t_data *data, t_philo *philo, int l_fork, int r_fork);
int		eat(t_data *data, t_philo *philo);

/* DIE */
int		check_i_die(t_data *data, t_philo *philo);

/* CLEANER */
void	clean(t_philo *philo, t_data *data, pthread_t *philo_arr);
void	clear_data(t_data *data);

/* TEST */
#endif
