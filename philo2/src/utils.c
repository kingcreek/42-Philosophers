/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:54:30 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/05 01:16:06 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * It takes a string and returns an integer
 * 
 * @param str The string to be converted.
 * 
 * @return the integer value of the string.
 */
int	ft_atoi(const char *str)
{
	int					is_char;
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	is_char = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
		is_char = 0;
	}
	if (sign == -1 || is_char || result != (int)sign * result)
		return (-2);
	return ((int)sign * result);
}

/**
 * It waits for a specified number of milliseconds
 * 
 * @param time the time to sleep in milliseconds
 */
void	msleep(int time)
{
	struct timeval	s_time;
	struct timeval	c_time;
	long long		start;
	long long		current;

	gettimeofday(&s_time, NULL);
	start = ((s_time.tv_usec / 1000) + (s_time.tv_sec * 1000));
	while (1)
	{
		gettimeofday(&c_time, NULL);
		current = ((c_time.tv_usec / 1000) + (c_time.tv_sec * 1000));
		if (current - start >= time)
			break ;
		usleep(50);
	}
}

/**
 * It returns the time in milliseconds since the last time it was called
 * 
 * @param data a pointer to the data structure
 * 
 * @return The time in milliseconds since the program started.
 */
int	get_time(t_data *data)
{
	struct timeval	now_time;
	long			sec;
	int				usec;

	gettimeofday(&now_time, NULL);
	sec = now_time.tv_sec;
	usec = now_time.tv_usec;
	return ((sec - data->tv_sec) * 1000 + ((usec - data->tv_usec) / 1000));
}

void	wait_until(t_data *data, int time)
{
	int		time_stamp;

	time_stamp = get_time(data);
	while (1)
	{
		usleep(100);
		if (get_time(data) - time_stamp >= time)
			return ;
	}
}
