/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:35:43 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:27:46 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_assign(t_fork *fork, t_philo *philo, int i)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[i];
		philo->second_fork = &fork[(i + 1) % philo->table->nbr_philo];
	}
	else
	{
		philo->second_fork = &fork[(i + 1) % philo->table->nbr_philo];
		philo->first_fork = &fork[i];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	while (++i < table->nbr_philo)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->time_eat = 0;
		philo->table = table;
		fork_assign(table->fork, philo, i);
		safe_mutex_handle(&philo->mutex, INIT);
	}
}

void	init(t_table *table)
{
	int	i;
	
	i = -1;
	table->end_sim = false;
	table->sim_ready = false;
	table->nbr_of_thread = 0;
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->philo = safe_malloc(sizeof(t_philo) * table->nbr_philo);
	table->fork = safe_malloc(sizeof(t_fork) * table->nbr_philo);
	while (++i < table->nbr_philo)
	{
		safe_mutex_handle(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i;
	}
	philo_init(table);
}