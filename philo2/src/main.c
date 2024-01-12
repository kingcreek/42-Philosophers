/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:54:10 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 16:41:52 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It's a loop that checks if the philosopher is dead, 
 * then checks if he can take the forks, then
 * checks if he's dead, then eats, then puts down the forks, 
 * then checks if he's eaten enough, then
 * sleeps, then prints a message
 * 
 * @param param the parameter passed to the thread
 * 
 * @return NULL
 */
void	*philo_loop(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->init_data;
	if (philo->id % 2 == 0)
		msleep(15);
	while (1)
	{
		if (!eat(data, philo))
			break ;
		if (philo->eat_count == data->must_eat)
			break ;
		if (!sleeping(data, philo))
			break ;
		if (!print_philo_msg(data, philo->id, THINK))
			break ;
	}
	return (NULL);
}

/**
 * It initializes the data for each philosopher, 
 * creates the threads, and then starts the threads
 * 
 * @param data a pointer to the struct that holds all
 *	           the data for the program
 * @param philo an array of t_philo structs, which is a 
 * 				struct that contains the data for each philosopher.
 * @param philo_arr an array of pthread_t's that will be used 
 * 					to create the threads
 */
void	lets_eat(t_data *data, t_philo *philo, pthread_t *philo_arr)
{
	int					i;
	struct timeval		start_time;

	i = 0;
	gettimeofday(&start_time, NULL);
	data->tv_sec = start_time.tv_sec;
	data->tv_usec = start_time.tv_usec;
	while (i < data->num_of_philo)
	{
		data->shared_fork[i] = 0;
		philo[i].init_data = data;
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].last_eat = 0;
		philo[i].last_eat_priv = 0;
		philo[i].forks = 0;
		pthread_mutex_init(&philo[i].last_eat_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&(philo_arr[i]), NULL, philo_loop, (void *) &philo[i]);
		i++;
	}
}

/**
 * It joins all the threads
 * 
 * @param data a struct that contains all the data that 
 * 			   is needed for the program to run.
 * @param philo_arr an array of pthread_t, which is the type of the thread.
 * @param philo an array of structs that contain the
 * 					 data for each philosopher
 * 
 * @return the value of the function pthread_join.
 */
int	join_threads(t_data *data, pthread_t *philo_arr, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(philo_arr[i], NULL) != 0)
		{
			clean(philo, data, philo_arr);
			return (0);
		}
	}
	return (1);
}

static void checker_loop(t_data *data, t_philo *philo)
{
	int	i;
	int	time;
	int	exit;

	exit = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_lock(&philo[i].last_eat_mutex);
			time = get_time(data);
			if (time - (philo[i].last_eat) > data->time_to_die)
			{
				print_philo_msg(data, philo[i].id, DEAD);
				exit = 1;
				pthread_mutex_unlock(&philo[i].last_eat_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo[i].last_eat_mutex);
			i++;
		}
		if (exit)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philo;
	pthread_t		*philo_arr;

	data = malloc(sizeof (t_data));
	if (!data)
		return (1);
	memset(data, 0, sizeof (t_data));
	if (start_init(argc, argv, data))
	{
		free(data);
		return (1);
	}
	philo_arr = malloc (sizeof(pthread_t) * (data->num_of_philo));
	philo = malloc (sizeof(t_philo) * (data->num_of_philo));
	if (!philo_arr || !philo)
	{
		free(philo_arr);
		free(philo);
		return (1);
	}
	lets_eat(data, philo, philo_arr);
	checker_loop(data, philo);
	if (!join_threads(data, philo_arr, philo))
		return (0);
	clean(philo, data, philo_arr);
	return (0);
}
