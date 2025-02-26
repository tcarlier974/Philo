/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 03:42:15 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 05:32:52 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

typedef enum s_opc
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opc;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_state;

typedef	struct s_table t_table;

typedef	struct s_fork
{
	long			fork_id;
	pthread_mutex_t	fork;
	
}			t_fork;


typedef struct s_philo
{
	int			id;
	long			time_eat;
	long			last_eat;
	bool			full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	mutex;
	pthread_t		thread_id;
	t_table			*table;
}			t_philo;

struct s_table
{
	long			nbr_philo;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			limit_of_meal;
	long			start_of_sim;
	long			nbr_of_thread;
	bool			end_sim;
	bool			sim_ready;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	t_fork			*fork;
	t_philo			*philo;
};

void	parse_arg(t_table *table, char **av);
void	error_exit(char *str);
void	init(t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread_id, void *(*func)(void *),
	void *arg, t_opc opcode);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opc opcode);
void	*monitor_dinner(void *param);
void	write_status(t_philo_state state, t_philo *philo);
bool	all_thread_running(pthread_mutex_t *mutex, long *nbr_of_thread,
	long nbr_of_philo);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	*dinner_thread(void *param);
void	increase_long(pthread_mutex_t *mutex, long *dest);
void	de_sync_philo(t_philo *philo);
void	clean(t_table *table);
void	dinner(t_table *table);
void	precise_sleep(long usec, t_table *table);
long	gettime(t_time_code time_code);
void	wait_all_thread(t_table *table);
bool	sim_end(t_table *table);
void	think(t_philo *philo, bool boole);

#endif