/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:20:22 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:19:51 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool boole)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!boole)
		write_status(THINKING, philo);
	if (philo->id % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(t_think * 0.5, philo->table);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->mutex, &philo->last_eat, gettime(MILLISECOND));
	write_status(EATING, philo);
	philo->time_eat++;
	precise_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_of_meal > 0
		&& philo->time_eat == philo->table->limit_of_meal)
		set_bool(&philo->mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_thread(void *param)
{
	t_philo	*philo;
	
	philo = (t_philo *)param;
	wait_all_thread(philo->table);
	set_long(&philo->mutex, &philo->last_eat, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->nbr_of_thread);
	de_sync_philo(philo);
	while (!sim_end(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_sleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	*lone_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	wait_all_thread(philo->table);
	set_long(&philo->mutex, &philo->last_eat, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->nbr_of_thread);
	write_status(TAKE_FIRST_FORK, philo);
	while (!sim_end(philo->table))
		usleep(200);
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_of_meal == 0)
		return ;
	else if (table->nbr_philo == 1)
	{
		safe_thread_handle(&table->philo[0].thread_id, lone_philo,
			&table->philo[0], CREATE);
	}
	else
	{
		while (++i < table->nbr_philo)
		{
			safe_thread_handle(&table->philo[i].thread_id, dinner_thread,
				&table->philo[i], CREATE);
		}
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_of_sim = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->sim_ready, true);
	i = -1;
	while (++i < table->nbr_philo)
		safe_thread_handle(&table->philo[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_sim, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
