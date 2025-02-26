/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 03:53:30 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 05:52:31 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	printf("NIGGA == >");
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
	printf("WIGGA\n");
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	printf("NIGGA32 == >\t");
	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	printf("WIGGA\n");
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	printf("NIGGA == >");
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
	printf("WIGGA\n");
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	printf("NIGGA == >");
	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	printf("WIGGA\n");
	return (ret);
}

bool	sim_end(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_sim));
}
