/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:22:51 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:43:53 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*num_index(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("only positive argument are accepted\n");
	if (!is_digit(*str))
		error_exit("only digits argument are accepted\n");
	num = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("only number under the INT_MAX value is accepted");
	return (num);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = num_index(str);
	while (is_digit(*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > __INT_MAX__)
		error_exit("only number under the INT_MAX value is accepted");
	return (nbr);
}

void	parse_arg(t_table *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		table->limit_of_meal = ft_atol(av[5]);
	else
		table->limit_of_meal = -1;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("use timestampl ager then 60ms");
}
