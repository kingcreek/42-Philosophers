/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 07:48:00 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 16:28:43 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It checks if any of the philosophers have died.
 * 
 * @param data the data structure that holds all the information about the game
 */
int	check_any_die(t_data *data)
{
	int	any_dead;

	pthread_mutex_lock(&(data->any_dead_mutex));
	any_dead = data->any_dead;
	pthread_mutex_unlock(&(data->any_dead_mutex));
	return (any_dead);
}

/**
 * It checks if the philosopher has died
 * 
 * @param data a pointer to the data structure that holds 
 * all the information about the simulation.
 * @param philo a pointer to the struct that contains 
 * all the information about the philosopher
 */
int	check_die(t_data *data, t_philo *philo)
{
	int	time;

	if (check_any_die(data))
		return (1);
	time = get_time(data);
	if (time - (philo->last_eat) > data->time_to_die)
	{
		print_philo_msg(data, philo->id, DEAD);
		return (1);
	}
	return (0);
}

/**
 * The function checks if a philosopher has died by 
 * comparing the current time with the time of their
 * last meal.
 * 
 * @param data A pointer to a struct that contains 
 * information about the simulation, such as the number
 * of philosophers, the time to die, and the time to eat.
 * @param philo A pointer to a struct representing a philosopher
 * in a dining philosophers problem. It
 * contains information such as the philosopher's ID, the time 
 * they last ate, and a mutex to protect
 * access to that time.
 * 
 * @return The function `check_die` is returning an integer value.
 * If the function detects that any
 * philosopher has died, it returns 1. If not, it returns 0.
 */
int	check_i_die(t_data *data, t_philo *philo)
{
	int	time;

	time = get_time(data);
	if (time - (philo->last_eat) > data->time_to_die)
	{
		print_philo_msg(data, philo->id, DEAD);
		return (1);
	}
	return (0);
}
