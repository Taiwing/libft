/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:57:52 by yforeau           #+#    #+#             */
/*   Updated: 2021/09/22 23:52:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef THREAD_SAFE

# define TS_ERR_BUF 1024

void			ft_mutex_lock(pthread_mutex_t *mutex)
{
	int		ret;
	char	err[TS_ERR_BUF];

	if (!(ret = pthread_mutex_lock(mutex)))
		return;
	ft_snprintf(err, TS_ERR_BUF, "pthread_mutex_lock: %s\n", strerror(ret));
	ft_exit(err, EXIT_FAILURE);
}

void			ft_mutex_unlock(pthread_mutex_t *mutex)
{
	int		ret;
	char	err[TS_ERR_BUF];

	if (!(ret = pthread_mutex_unlock(mutex)))
		return;
	ft_snprintf(err, TS_ERR_BUF, "pthread_mutex_unlock: %s\n", strerror(ret));
	ft_exit(err, EXIT_FAILURE);
}

#endif
