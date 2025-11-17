/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_in_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:25:43 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/17 17:43:53 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_rules(t_data *shared, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		write(2, "./philosophers number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
		return (-1);
	}
	shared->total_philos = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->eat_time = ft_atoi(argv[3]);
	shared->sleep_time = ft_atoi(argv[4]);
	if (argc >= 6)
		shared->meal_amount = ft_atoi(argv[5]);
	else
		shared->meal_amount = -1;
	if (shared->total_philos < 1 || shared->total_philos > 250)
		return (write(2, "total_philos not 1-250 or overflow\n", 45), -1);
	if (shared->time_to_die < 10)
		return (write(2, "time_to_die too low or overflowed\n", 35), -1);
	if (shared->eat_time < 10)
		return (write(2, "eat_time too low or overflowed\n", 32), -1);
	if (shared->sleep_time < 10)
		return (write(2, "sleep_time too low or overflowed\n", 34), -1);
	if (argc >= 6 && shared->meal_amount < 1)
		return (write(2, "meal_amount too low or overflowed\n", 35), -1);
	return (0);
}

int	init_program(t_data *shared, t_philosopher *philo)
{
	size_t	iter;

	iter = 0;
	shared->death = 0;
	if (pthread_mutex_init(&shared->print, NULL) != 0)
		return (write(2, "mutex init failed\n", 19), -1);
	while (iter < shared->total_philos)
	{
		if (pthread_mutex_init(&shared->forks[iter].key, NULL) != 0)
			return (cleanup(shared, philo, iter), -1);
		if (pthread_mutex_init(&philo[iter].meal_info, NULL) != 0)
			return (pthread_mutex_destroy(&shared->forks[iter].key),
				cleanup(shared, philo, iter), -1);
		philo[iter].shared = shared;
		philo[iter].id = iter;
		iter++;
	}
	return (0);
}

int	cleanup(t_data *shared, t_philosopher *philo, int amount)
{
	size_t	iter;

	iter = 0;
	while (iter < amount)
	{
		pthread_join(shared->threads[iter], NULL);
		pthread_mutex_destroy(&philo[iter].meal_info);
		pthread_mutex_destroy(&shared->forks[iter].key);
		iter++;
	}
	pthread_mutex_destroy(&shared->print);
	return (0);
}

void	stopwatch(t_data *shared, t_philosopher *philo)
{
	while (1)
	{
		if (end_check(shared, philo) == DEATH)
			break ;
		usleep(200);
	}
}
