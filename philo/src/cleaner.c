/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:05:50 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/02 23:14:00 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It destroys all the mutexes and frees the array of pthreads
 * 
 * @param philo an array of structs that contain the information 
 * 					 for each philosopher
 * @param data a struct that contains all the data that is shared 
 * 			   between threads.
 * @param philo_arr an array of pthread_t's that will be used to 
 * 					create the threads
 */
void	clean(t_philo *philo, t_data *data, pthread_t *philo_arr)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&(philo[i].last_eat_mutex));
		free(data->fork_mutex[i]);
		i++;
	}
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(data->time_mutex);
	clear_data(data);
	free(philo_arr);
	free(philo);
}

/**
 * It frees the memory allocated for the shared fork,
 * the mutexes, and the time mutex
 * 
 * @param data a pointer to the data structure
 */
void	clear_data(t_data *data)
{
	free(data->shared_fork);
	free(data->fork_mutex);
	free(data->time_mutex);
	free(data);
}
