/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:39:30 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/17 18:17:26 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*even_total_and_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1].key;
	else
		left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	efficient_sleep(me->shared->start_time - get_time());
	while (1)
	{
		if (eat(me, right_fork, left_fork, RIGHT) != 0)
			return (NULL);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		good_night(me);
		if (output(me, "%lld %d is thinking\n", NO))
			return (NULL);
	}
	return (NULL);
}

void	*even_total_odd_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	efficient_sleep(me->shared->start_time - get_time());
	while (1)
	{
		good_night(me);
		if (output(me, "%lld %d is thinking\n", NO))
			return (NULL);
		if (eat(me, left_fork, right_fork, LEFT) != 0)
			return (NULL);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	return (NULL);
}

void	*odd_total_even_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1].key;
	else
		left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	efficient_sleep(me->shared->start_time - get_time());
	while (1)
	{
		if (eat(me, right_fork, left_fork, RIGHT) != 0)
			return (NULL);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		good_night(me);
		think(me, me->shared->eat_time * 2 - me->shared->sleep_time);
	}
	return (NULL);
}

void	*odd_total_and_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	efficient_sleep(me->shared->start_time - get_time());
	while (1)
	{
		if (get_time() - me->shared->start_time < 10)
			think(me, me->shared->eat_time);
		else
			think(me, me->shared->eat_time * 2 - me->shared->sleep_time);
		if (eat(me, left_fork, right_fork, LEFT) != 0)
			return (NULL);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		good_night(me);
	}
	return (NULL);
}

void	*last_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher *)data;
	left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	efficient_sleep(me->shared->start_time - get_time());
	while (1)
	{
		if (get_time() - me->shared->start_time < 10)
			think(me, me->shared->eat_time * 2);
		else
			think(me, me->shared->eat_time * 2 - me->shared->sleep_time);
		if (eat(me, right_fork, left_fork, RIGHT) != 0)
			return (NULL);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		good_night(me);
	}
	return (NULL);
}
