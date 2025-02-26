/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 03:40:12 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:45:01 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_thread(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->sim_ready))
		;
}

bool	all_thread_running(pthread_mutex_t *mutex, long *nbr_of_thread,
	long nbr_of_philo)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	if (nbr_of_philo == *nbr_of_thread)
		ret = true;
	else
		ret = false;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	de_sync_philo(t_philo *philo)
{
	if (philo->table->nbr_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_sleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}
