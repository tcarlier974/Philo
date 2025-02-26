/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:40:27 by tcarlier          #+#    #+#             */
/*   Updated: 2025/02/26 06:46:56 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("error during a call to malloc\n");
	return (ret);
}

static void	mutex_error(int status, t_opc opcode)
{
	if (status == 0)
	return ;
	else if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK
		|| opcode == DESTROY))
		error_exit("the value specified by mutex is invalid\n");
	else if (EINVAL == status && (opcode == INIT))
		error_exit("the value specified by attr is invalid\n");
	else if (EDEADLK == status)
		error_exit("A dead lock would occur"
			" if the thread blocked waiting for mutex\n");
	else if (EPERM == status)
		error_exit("the current thread does not hold a lock on mutex\n");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create"
			" another mutex\n");
	else if (EBUSY == status)
		error_exit("Mutex is locked\n");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_opc opcode)
{
	if (opcode == LOCK)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong opcode for the mutex handle"
			" use <LOCK UNLOCK INIT DESTROY>\n");
}

static void	thread_error(int status, t_opc opcode)
{
	if (status == 0)
	return ;
	if (EAGAIN == status)
		error_exit("Insufficient resources to create another thread\n");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate perimission\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid\n");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that specified"
			" by the given thread ID, thread\n");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies"
			" the calling thread\n");
}

void	safe_thread_handle(pthread_t *thread_id, void *(*func)(void *),
	void *arg, t_opc opcode)
{
	if (opcode == CREATE)
		thread_error(pthread_create(thread_id, NULL, func, arg), opcode);
	else if (opcode == JOIN)
		thread_error(pthread_join(*thread_id, NULL), opcode);
	else if (opcode == DETACH)
		thread_error(pthread_detach(*thread_id), opcode);
	else
		error_exit("wrong opcode for the thread handle"
			" use <CREATE JOIN DETACH>\n");
}
