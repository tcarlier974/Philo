/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:10:22 by tcarlier          #+#    #+#             */
/*   Updated: 2025/03/28 15:05:21 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_exit("wrong input\nplease use :\t"
			"./philo nb_philo time_die time_eat time_sleep [must_eat]\n");
	parse_arg(&table, av);
	init(&table);
	dinner(&table);
	clean(&table);
	return (0);
}
