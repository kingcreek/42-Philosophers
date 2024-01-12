/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 07:48:00 by imurugar          #+#    #+#             */
/*   Updated: 2024/01/12 20:58:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (time - (philo->last_eat_priv) > data->time_to_die)
	{
		return (1);
	}
	return (0);
}