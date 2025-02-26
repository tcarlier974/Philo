/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 03:35:37 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 05:35:36 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_state state, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_of_sim;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if ((TAKE_FIRST_FORK == state || TAKE_SECOND_FORK == state)
		&& !sim_end(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == state && !sim_end(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == state && !sim_end(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == state && !sim_end(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == state)
		printf("%-6ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
