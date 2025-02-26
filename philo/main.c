/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:10:22 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:29:54 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_exit("wrong input\n\t./philosophers nb_p t_d t_e t_s [m_e]\n");
	parse_arg(&table, av);
	init(&table);
	dinner(&table);
	clean(&table);
	return (0);	
}
