/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:28:57 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/18 14:23:09 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	create_thread(t_philosopher *philo, t_data *shared,
	size_t iter, void *(*thread_function)(void *))
{
	if (pthread_create(&shared->threads[iter], NULL,
			thread_function, &philo[iter]) != 0)
		return (creation_fail(philo, shared, iter), -1);
	return (0);
}

void	*lonely_philo(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	right_fork = &me->shared->forks[me->id].key;
	pthread_mutex_lock(right_fork);
	if (output(me, "%lld %d has taken a fork\n", RIGHT))
		return (NULL);
	efficient_sleep(me->shared->time_to_die);
	pthread_mutex_unlock(right_fork);
	return (NULL);
}

int	lonely_philo_setup(t_philosopher *philo, t_data *shared)
{
	shared->start_time = get_time();
	philo[0].last_meal = shared->start_time;
	philo[0].meal_count = 0;
	if (pthread_create(&shared->threads[0], NULL, lonely_philo, &philo[0]) != 0)
	{
		cleanup(shared, philo, 0, CREATION_FAIL);
		return (write(2, "creation of threads failed!\n", 29), -1);
	}
	return (0);
}

int	even_philo_setup(t_philosopher *philo, t_data *shared)
{
	size_t	iter;

	iter = 0;
	shared->start_time = get_time() + 10;
	while (iter < shared->total_philos)
	{
		philo[iter].last_meal = shared->start_time;
		philo[iter].meal_count = 0;
		if (!(philo[iter].id & 1))
		{
			if (create_thread(philo, shared, iter, even_total_and_id) == -1)
				return (-1);
		}
		else
		{
			if (create_thread(philo, shared, iter, even_total_odd_id) == -1)
				return (-1);
		}
		iter++;
	}
	return (0);
}

int	odd_philo_setup(t_philosopher *philo, t_data *shared)
{
	size_t	iter;

	iter = 0;
	shared->start_time = get_time() + 10;
	while (iter < shared->total_philos)
	{
		philo[iter].last_meal = shared->start_time;
		philo[iter].meal_count = 0;
		if (philo[iter].id == shared->total_philos - 1)
		{
			if (create_thread(philo, shared, iter, last_id) == -1)
				return (-1);
		}
		else if (!(philo[iter].id & 1))
		{
			if (create_thread(philo, shared, iter, odd_total_even_id) == -1)
				return (-1);
		}
		else if (create_thread(philo, shared, iter, odd_total_and_id) == -1)
			return (-1);
		iter++;
	}
	return (0);
}
