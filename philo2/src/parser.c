/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:07:23 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/02 23:14:16 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It checks if the number of arguments is valid
 * 
 * @param argc the number of arguments passed to the program
 * 
 * @return the value of the argument count.
 */
int	check_nbr_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_invalid(0);
		return (1);
	}
	return (0);
}

/**
 * It checks the validity of the input arguments 
 * and stores them in the t_data struct
 * 
 * @param argc the number of arguments passed to the program
 * @param argv 
 * @param data a pointer to the data structure that holds 
 * all the information about the simulation.
 * 
 * @return the value of the expression.
 */
int	init_input(int argc, char **argv, t_data *data)
{
	if (check_nbr_args(argc))
		return (1);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (data->num_of_philo <= 0)
		return (print_invalid(0), 1);
	else if (data->time_to_die <= 0)
		return (print_invalid(1), 1);
	else if (data->time_to_eat <= 0)
		return (print_invalid(2), 1);
	else if (data->time_to_sleep <= 0)
		return (print_invalid(3), 1);
	else if (data->must_eat <= 0 && argc == 6)
		return (print_invalid(4), 1);
	return (0);
}

/**
 * It initializes the data structure
 * 
 * @param argc the number of arguments passed to the program
 * @param argv the arguments passed to the program
 * @param data a pointer to the data structure that holds 
 * all the information about the simulation.
 * 
 * @return the value of the function init_input.
 */
int	start_init(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (init_input(argc, argv, data))
		return (1);
	data->shared_fork = malloc(sizeof(char) * data->num_of_philo);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t *) * data->num_of_philo);
	data->time_mutex = malloc (sizeof(pthread_mutex_t));
	//data->any_dead_mutex = malloc (sizeof(pthread_mutex_t));
	if (!data->shared_fork || !data->fork_mutex || !data->time_mutex)
	{
		clear_data(data);
		return (1);
	}
	pthread_mutex_init(data->time_mutex, NULL);
	while (i < data->num_of_philo)
	{
		data->fork_mutex[i] = malloc(sizeof (pthread_mutex_t));
		if (!data->fork_mutex[i])
			return (1);
		pthread_mutex_init(data->fork_mutex[i], NULL);
		i++;
	}
	data->any_dead = 0;
	pthread_mutex_init(&(data->any_dead_mutex), NULL);
	pthread_mutex_init(&(data->print_mutex), NULL);
	return (0);
}
