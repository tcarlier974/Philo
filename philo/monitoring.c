/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 03:23:04 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 05:34:53 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->mutex,
		&philo->last_eat);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *param)
{
	t_table	*table;
	int		i;
	
	table = (t_table *)param;
	while (!all_thread_running(&table->table_mutex, &table->nbr_of_thread,
		table->nbr_philo))
		;
	while (!sim_end(table))
	{
		i = -1;
		while (++i < table->nbr_philo && !sim_end(table))
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				write_status(DIED, table->philo + i);
			}
		}
	}
	return (NULL);
}