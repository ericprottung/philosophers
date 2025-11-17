/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:24:34 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/17 17:38:21 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_data			shared;
	t_philosopher	philo[250];
	int				status;

	if (init_rules(&shared, argc, argv) == -1)
		return (1);
	init_program(&shared, philo);
	if (shared.total_philos == 1)
		status = lonely_philo_setup(philo, &shared);
	else if (shared.total_philos % 2 == 0)
		status = even_philo_setup(philo, &shared);
	else
		status = odd_philo_setup(philo, &shared);
	if (status == FAIL)
		return (1);
	stopwatch(&shared, philo);
	cleanup(&shared, philo, shared.total_philos);
	return (0);
}
