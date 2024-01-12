/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:54:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 01:46:53 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It prints a message about a philosopher's action, 
 * but only if the philosopher is still alive
 * 
 * @param data the data structure that contains all 
 * the information about the simulation
 * @param philo_id the id of the philosopher
 * @param msg_nbr 0 = has taken a fork, 1 = is eating, 
 * 2 = is sleeping, 3 = is thinking, 4 = died
 * 
 * @return The time in milliseconds since the program started.
 */
int	print_philo_msg(t_data *data, int philo_id, int msg_nbr)
{
	int	time_stamp;
	
	pthread_mutex_lock(&(data->any_dead_mutex));
	if (data->any_dead)
		return (pthread_mutex_unlock(&(data->any_dead_mutex)), 0);
	pthread_mutex_unlock(&(data->any_dead_mutex));
	pthread_mutex_lock(&(data->print_mutex));
	time_stamp = get_time(data);
	if (msg_nbr == FORK)
		printf("%d %d has taken a fork\n", time_stamp, philo_id);
	else if (msg_nbr == EAT)
		printf("%d %d is eating\n", time_stamp, philo_id);
	else if (msg_nbr == SLEEP)
		printf("%d %d is sleeping\n", time_stamp, philo_id);
	else if (msg_nbr == THINK)
		printf("%d %d is thinking\n", time_stamp, philo_id);
	else if (msg_nbr == DEAD)
	{
		pthread_mutex_lock(&(data->any_dead_mutex));
		data->any_dead = 1;
		pthread_mutex_unlock(&(data->any_dead_mutex));
		printf("%d %d died\n", time_stamp, philo_id);
	}
	pthread_mutex_unlock(&(data->print_mutex));
	return (1);
}

/**
 * It prints an error message based on the integer passed to it
 * 
 * @param msg_nbr The number of the error message to print.
 */
void	print_invalid(int msg_nbr)
{
	if (msg_nbr == 0)
		printf("Invalud number of philosophers\n");
	else if (msg_nbr == 1)
		printf("Time to die must be >= 0\n");
	else if (msg_nbr == 2)
		printf("Time to eat must be > 0\n");
	else if (msg_nbr == 3)
		printf("Time to sleep must be > 0\n");
	else if (msg_nbr == 4)
		printf("The number of meals should be > 0 or unspecified\n");
}
