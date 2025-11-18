/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:32:59 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/18 16:23:57 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	return_number;

	i = 0;
	sign = 1;
	return_number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		return_number *= 10;
		return_number += str[i] - 48;
		i++;
		if (return_number > 2147483647 || return_number < -21474836438)
			return (-1);
	}
	return_number *= (long)sign;
	return ((int)return_number);
}

void	unlock_forks(t_philosopher *me, int eat_call)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1].key;
	else
		left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	if (eat_call == BOTH)
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	else if (eat_call == LEFT)
		pthread_mutex_unlock(left_fork);
	else if (eat_call == RIGHT)
		pthread_mutex_unlock(right_fork);
}

void	efficient_sleep(long long duration)
{
	long long	start;

	start = get_time();
	if (duration > 2)
		usleep((duration - 2) * 1000);
	while (get_time() - start < duration)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec + 500) / 1000);
}

void	creation_fail(t_philosopher *philo, t_data *shared, size_t amount)
{
	end(&philo[0], CREATION_FAIL);
	cleanup(shared, philo, amount, CREATION_FAIL);
}
