/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:54:22 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 01:47:01 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It checks if the fork is available, if it is, it takes it, 
 * and prints a message
 * 
 * @param r the data structure that holds all the data for the simulation
 * @param p the current philo
 * @param pos the position of the fork in the array of forks
 */
void	check_fork(t_data *data, t_philo *philo, int pos)
{
	pthread_mutex_lock(data->fork_mutex[pos]);
	if (data->shared_fork[pos] == 0)
	{
		data->shared_fork[pos] = 1;
		philo->forks += 1;
		if (!check_die(data, philo))
			print_philo_msg(data, philo->id, 0);
	}
	pthread_mutex_unlock(data->fork_mutex[pos]);
}

/**
 * It checks if the philosopher has both forks, if not 
 * it checks if the philosopher can take the left
 * fork, then the right fork, and if the philosopher 
 * has both forks it eats, then puts down the forks
 * 
 * @param data a pointer to the data structure
 * @param philo the current philosopher
 */
void	eat(t_data *data, t_philo *philo)
{
	int			left_fork;
	int			right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % data->num_of_philo;
	if (philo->id % 2 == 0)
	{
		left_fork = philo->id % data->num_of_philo;
		right_fork = philo->id - 1;
	}
	while (philo->forks < 2 && !check_i_die(data, philo))
	{
		check_fork(data, philo, left_fork);
		check_fork(data, philo, right_fork);
	}
	if (!check_die(data, philo))
	{
		philo->last_eat = get_time(data);
		print_philo_msg(data, philo->id, 1);
		wait_until(data, philo, data->time_to_eat);
		philo->eat_count++;
		putdown_fork(data, philo, left_fork, right_fork);
	}
}

/**
 * It locks the left fork, sets it to 0, unlocks it, 
 * locks the right fork, sets it to 0, unlocks it,
 * and sets the philo's forks to 0
 * 
 * @param data a pointer to the data struct
 * @param philo a pointer to the current philo's struct
 * @param l_fork the left fork
 * @param r_fork the right fork
 */
void	putdown_fork(t_data *data, t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(data->fork_mutex[l_fork]);
	data->shared_fork[l_fork] = 0;
	pthread_mutex_unlock(data->fork_mutex[l_fork]);
	pthread_mutex_lock(data->fork_mutex[r_fork]);
	data->shared_fork[r_fork] = 0;
	pthread_mutex_unlock(data->fork_mutex[r_fork]);
	philo->forks = 0;
}

/**
 * It prints a message and sleeps for a certain amount of time
 * 
 * @param philo a pointer to the current philo's struct
 */
void	sleeping(t_data *data, t_philo *philo)
{
	print_philo_msg(philo->init_data, philo->id, 2);
	wait_until(data, philo, data->time_to_sleep);
}
